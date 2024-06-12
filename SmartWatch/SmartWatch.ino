#include "User_input.h"
<<<<<<< Updated upstream
#include "Notification_sender.h"
#include "Battery_monitoring.h"
#include "OLED_display.h"
#include "GPS.h"
#include "Data_base_retriever.h"

// Declare instances
OLED_display display;
Battery_monitoring batteryMonitor(display);
User_input userButton(2); // Assuming the button is connected to pin 2
Notification_sender notifier;
GPS gps;

void setup() {
  Serial.begin(9600);
  display.initialize_display();
  userButton.begin();
  gps.detect_location();
}

void loop() {
  // Handle button input
  if (userButton.long_press_panic()) {
    Serial.println("Emergency! Long press detected.");
    notifier.send_alert_message(gps, 1234567890, "contact@example.com"); // Replace with actual contact info
=======
#include "Oled_display.h"
#include "BatteryMonitor.h"
#include "Notification_sender.h"
#include <esp_task_wdt.h>

// Define WiFi credentials
const char* ssid = "K9";
const char* password = "saifceo20";

// Create an object instance
User_input user_input;
mpu_algo mp;
Oled_display oled;
BatteryMonitor batteryMonitor(34); // ADC pin for battery voltage measurement
Notification_sender notificationSender; // Add Notification_sender object

// Task Function declarations
void readMPUTask(void *pvParameters);
void handleUserInputTask(void *pvParameters);
void updateDisplayTask(void *pvParameters);
void getCurrentTimeTask(void *pvParameters);
void readBatteryTask(void *pvParameters);

#define WDT_TIMEOUT 3

<<<<<<< Updated upstream
=======
const char* ssid = "TP-Link_36A6";
const char* password = "44423315";


>>>>>>> Stashed changes
void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  notificationSender.initialize_WiFi();
  oled.initialize_ntp();

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
  xTaskCreate(handleExerciseButtonTask, "ExerciseButtonTask", 8000, NULL, 2, NULL);
  xTaskCreate(handleFallDetectionTask, "FallDetectionTask", 4096, NULL, 2, NULL);
  xTaskCreate(updateDisplayTask, "DisplayTask", 8000, NULL, 1, NULL);
  xTaskCreate(getCurrentTimeTask, "GetCurrentTime", 2000, NULL, 1, NULL);
  xTaskCreate(readBatteryTask, "ReadBatteryTask", 2000, NULL, 1, NULL);
}

// Set flags
bool initial_display_flag = true;
bool user_input_flag = false;
bool display_alert_sent = false;
bool exercise_mode_flag = false;
bool exercise_mode_deactivated_flag = false;

// Set timers
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
  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  while (true) {
    user_input.handle_exercise_button();
    check_exercise_mode();
    check_exercise_mode_cancel();
    // To stop the exercise mode in the beginning
    if (x == 0) {
      reset_flags_and_timers();
      x++;
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
>>>>>>> Stashed changes
  }

<<<<<<< Updated upstream
  if (userButton.deny_emergency_press()) {
    Serial.println("Emergency denied.");
    // Add code to cancel the emergency here
=======
// Task for handling fall detection
void handleFallDetectionTask(void * parameter) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  while (true) {
    mp.readFall();
    vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50ms
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
>>>>>>> Stashed changes
  }

<<<<<<< Updated upstream
  // Monitor and display battery life
  batteryMonitor.read_battery_life();
  batteryMonitor.display_battery_life();
  
  Serial.print("Battery Life: ");
  Serial.print(batteryMonitor.get_battery_life());
  Serial.println("%");

  delay(60000); // Update battery life every minute
}
=======
// Task for updating the OLED display
void updateDisplayTask(void * parameter) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  while (true) {
    if (exercise_mode_flag) {
      handle_exercise_mode();
    } else if (exercise_mode_deactivated_flag) {
      handle_exercise_mode_deactivation();
    } else {
      initial_display();
      handle_fall_detection();
      handle_user_input();
    }
    handle_alert_sent();

    // Update battery status on the display
    batteryMonitor.readBattery(); // Ensure the battery value is updated here
    oled.display_battery_status(batteryMonitor.getBatteryVoltage(), batteryMonitor.getBatteryPercentage(), 0, 0);

    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  }
}

// Task for getting current time
void getCurrentTimeTask(void *pvParameters) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  while (true) {
    oled.get_local_time();
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  }
}

// Task for reading battery status
void readBatteryTask(void *pvParameters) {
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  while (true) {
    batteryMonitor.readBattery();
    vTaskDelay(pdMS_TO_TICKS(5000)); // Update battery status every 5 seconds
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  }
}

void check_exercise_mode() {
  // Check if exercise mode button pressed
  if (user_input.shortPressDetected) {
    Serial.println("Exercise button pressed!!");
    exercise_mode_flag = true;
  }
}

void check_exercise_mode_cancel() {
  // Check if exercise long press to deactivate the long press is pressed.
  if (exercise_mode_flag && user_input.longPressDetected) {
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

void handle_alert_sent() {
  if (user_input.long_press_panic()) display_alert_sent = true;

  if (display_alert_sent) {
    exercise_mode_deactivated_flag = false;
    exercise_mode_flag = false;
    mp.fall_detected = false;
    initial_display_flag = false;
    user_input_flag = false;
    Serial.print(user_input.long_press_panic());
    if (alert_sent_start_time == 0) alert_sent_start_time = millis();

    oled.display_string("Alert sent!", 15, 75);

    if ((millis() - alert_sent_start_time) > 5000ul) {
      initial_display_flag = true;
      reset_flags_and_timers();
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

void handle_exercise_mode() {
  oled.display_long_string("Exercise", "Mode", 30, 75, 40, 95);
  mp.exercise_mode_fall_detection();
  if (exercise_mode_start_time == 0) exercise_mode_start_time = millis();
  if ((millis() - exercise_mode_start_time) > 600000ul) {
    exercise_mode_flag = false;
    exercise_mode_deactivated_flag = true;
  }
}

void handle_exercise_mode_deactivation() {
  oled.display_long_string("Exercise", "Deactivated", 30, 75, 10, 95);
  if (exercise_mode_deactivated_time == 0) exercise_mode_deactivated_time = millis();
  if ((millis() - exercise_mode_deactivated_time) > 2000ul) {
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
>>>>>>> Stashed changes
