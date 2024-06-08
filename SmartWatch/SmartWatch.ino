#include <Wire.h>
#include "mpu_algo.h"
#include "User_input.h"
#include "Oled_display.h"
#include <esp_task_wdt.h>


// Create an object instance
User_input user_input;
mpu_algo mp; 
Oled_display oled;


// Task Function declarations
void readMPUTask(void *pvParameters);
void handleUserInputTask(void *pvParameters);
void updateDisplayTask(void *pvParameters);


#define WDT_TIMEOUT 3


void setup() {
  Serial.begin(115200);

 esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WDT_TIMEOUT * 1000, // Convert seconds to milliseconds
    .trigger_panic = true // Trigger panic (reset) if WDT times out
  };

  esp_task_wdt_init(&wdt_config); // Initialize the watchdog timer
  esp_task_wdt_add(NULL); // Add current task (main loop) to the watchdog timer

  user_input.initialize_buttons();
  oled.initialize_display();
  mp.initialize_mpu();

 // Create FreeRTOS tasks
  xTaskCreate(handleExerciseButtonTask, "ExerciseButtonTask", 8000, NULL, 1, NULL);
  xTaskCreate(handleFallDetectionTask, "FallDetectionTask", 4096, NULL, 2, NULL);
  xTaskCreate(handleDisplayTask, "DisplayTask", 8000, NULL, 2, NULL);
}


//set flags
bool initial_display_flag = true;
bool user_input_flag = false;
bool display_alert_sent = false;
bool exercise_mode_flag = false;
bool exercise_mode_deactivated_flag = false;


// set timers
unsigned long are_you_ok_start_time = 0ul;
unsigned long alert_sent_start_time = 0ul;
unsigned long user_denial_start_time = 0ul;
unsigned long exercise_mode_start_time = 0ul;
unsigned long exercise_mode_deactivated_time = 0ul;


int x = 0;


void loop() {

  esp_task_wdt_reset();

}


// Task for handling exercise button
void handleExerciseButtonTask(void * parameter) {

  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  while(true) {
    user_input.handle_exercise_button();
    check_exercise_mode();
    check_exercise_mode_cancel();
      // to stop the Excersice mode in the beginning
    if (x == 0){
    reset_flags_and_timers();
    x++;
    }

    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 10ms

   uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  }
}


// Task for handling fall detection
void handleFallDetectionTask(void * parameter) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  while(true) {
    mp.readFall();
    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100ms
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  }
}


// Task for handling OLED display updates
void handleDisplayTask(void * parameter) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  while(true) {
    if (exercise_mode_flag) {
      handle_exercise_mode();
    } else if (exercise_mode_deactivated_flag) {
      handle_exercise_mode_deactivation();
    } else {
       initial_display();
       handle_fall_detection();
       handle_alert_sent();
       handle_user_input();
    }
    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100ms
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  }
}








void check_exercise_mode(){
     // Check if excersice mode button pressed
   if (user_input.shortPressDetected == true){
    Serial.println("Exercise button pressed!!");
    exercise_mode_flag = true;
  }
}

void check_exercise_mode_cancel(){
  // check if exercise long press to deactivate the long press is pressed.
  if((exercise_mode_flag == true) && (user_input.longPressDetected == true)) {
   exercise_mode_flag = false;
   exercise_mode_deactivated_flag = true;
  }

}



void initial_display() {
  if (initial_display_flag) {
    oled.display_string("Initial state", 15, 75);
    reset_flags_and_timers();
  }
}



void handle_fall_detection() {
  if (mp.fall_detected) {
    initial_display_flag = false;
    display_alert_sent = false;
    user_input_flag = false;

    oled.display_string("Are you ok?", 6, 75);


    if (are_you_ok_start_time == 0) are_you_ok_start_time = millis();
      

    if ((millis() - are_you_ok_start_time) > 10000ul) {
      are_you_ok_start_time = 0ul;
      mp.fall_detected = false;
      display_alert_sent = true;
    }
  }
}

void handle_alert_sent() 
{

  if(user_input.long_press_panic()) display_alert_sent = true;
  
  if (display_alert_sent ) 
  {
    mp.fall_detected = false;
    initial_display_flag = false;
    user_input_flag = false;
    Serial.print(user_input.long_press_panic());
    if (alert_sent_start_time == 0) alert_sent_start_time = millis();
      

    oled.display_string("Alert sent!", 15, 75);
   

    if ((millis() - alert_sent_start_time) > 5000ul) 
    {
      initial_display_flag = true;
      alert_sent_start_time = 0ul;
      display_alert_sent = false;

    }
  }
}

void handle_user_input() {
  if (user_input.deny_emergency_press() && mp.fall_detected) {
    user_input_flag = true;
    display_alert_sent = false;
    mp.fall_detected = false;
    initial_display_flag = false;
  }

  if (user_input_flag) {
    oled.display_string("Good to hear!", 4, 75);

    if (user_denial_start_time == 0ul) {
      user_denial_start_time = millis();
    }

    if ((millis() - user_denial_start_time) > 3000ul) {
      initial_display_flag = true;
      user_denial_start_time = 0ul;
      reset_flags_and_timers(); 
    }
  }
}





void handle_exercise_mode(){

   oled.display_long_string("Exercise", "Mode", 30, 75, 40, 95);

   mp.exercise_mode_fall_detection();

   if(exercise_mode_start_time == 0) exercise_mode_start_time = millis();
  
   
   if((millis() - exercise_mode_start_time) > 600000ul){
    exercise_mode_flag = false;
    exercise_mode_deactivated_flag = true;
   }
  
}


void handle_exercise_mode_deactivation(){

  oled.display_long_string("Exercise", "Deactivated", 30, 75, 10, 95);

  if (exercise_mode_deactivated_time == 0) exercise_mode_deactivated_time = millis();

  if((millis() - exercise_mode_deactivated_time) > 2000ul){
    exercise_mode_deactivated_flag = false;
    initial_display_flag = true;
    reset_flags_and_timers();
  }
 
}


void reset_flags_and_timers() {
  are_you_ok_start_time = 0ul;
  alert_sent_start_time = 0ul;
  user_denial_start_time = 0ul;
  exercise_mode_start_time = 0ul;
  exercise_mode_deactivated_time = 0ul;


  exercise_mode_flag = false;
  exercise_mode_deactivated_flag = false;
  display_alert_sent = false;
  user_input_flag = false;
}