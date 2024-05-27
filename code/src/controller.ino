#include "mpu_algo.h"
#include "User_input.h"
#include "Oled_display.h"


// Create an object instance
User_input user_input;
mpu_algo mp; 
Oled_display oled;


void setup() {
  Serial.begin(115200);

  user_input.initialize_buttons();
  oled.initialize_display();
  mp.initialize_mpu();
}

//set flags
bool initial_display_flag = true;
bool user_input_flag = false;
bool display_alert_sent = false;


// set timers
unsigned long are_you_ok_start_time = 0ul;
unsigned long alert_sent_start_time = 0ul;
unsigned long user_denial_start_time = 0ul;


void loop() {

  mp.readFall();

  initial_display();
  handle_fall_detection();
  handle_alert_sent();
  handle_user_input();

}


void initial_display() {
  if (initial_display_flag) {
    display_initial_message();
    reset_flags_and_timers();
  }
}


void handle_fall_detection() {
  if (mp.fall_detected) {
    initial_display_flag = false;
    display_alert_sent = false;
    user_input_flag = false;

    display_are_you_ok_after_fall_detection();


    if (are_you_ok_start_time == 0) are_you_ok_start_time = millis();
      

    if ((millis() - are_you_ok_start_time) > 10000ul) {
      are_you_ok_start_time = 0ul;
      mp.fall_detected = false;
      display_alert_sent = true;
    }
  }
}

void handle_alert_sent() {

  if(user_input.long_press_panic()) display_alert_sent = true;
  
  if (display_alert_sent ) {
    mp.fall_detected = false;
    initial_display_flag = false;
    user_input_flag = false;
    Serial.print(user_input.long_press_panic());
    if (alert_sent_start_time == 0) alert_sent_start_time = millis();
      

    display_alert_sent_if_user_didnot_input();

    if ((millis() - alert_sent_start_time) > 10000ul) {
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
    display_after_users_denial();

    if (user_denial_start_time == 0ul) {
      user_denial_start_time = millis();
    }

    if ((millis() - user_denial_start_time) > 5000ul) {
      initial_display_flag = true;
      user_denial_start_time = 0ul;
      reset_flags_and_timers(); 
    }
  }
}

void reset_flags_and_timers() {
  are_you_ok_start_time = 0ul;
  alert_sent_start_time = 0ul;
  user_denial_start_time = 0ul;
  display_alert_sent = false;
  user_input_flag = false;
}

// Functions for displaying messages
void display_initial_message() {
  oled.clear_display();
  oled.display_string("Initial state");
}

void display_are_you_ok_after_fall_detection() {
  oled.clear_display();
  oled.display_string("Are you ok?");
}

void display_alert_sent_if_user_didnot_input() {
  oled.clear_display();
  oled.display_string("Alert sent!");
}

void display_after_users_denial() {
  oled.clear_display();
  oled.display_string("Good to hear!");
}

