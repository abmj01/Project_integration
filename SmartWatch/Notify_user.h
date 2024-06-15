#ifndef NOTIFY_USER_H
#define NOTIFY_USER_H

#include <Arduino.h>


#define buzzer_pin 33  // pin 14 in pcb not available in TTGO module

class Notify_user {
private:

  const unsigned long alert_duration = 10000;  // 10 seconds

public:

  unsigned long startMillis = 0;    // Store the start time, initialized to 0
  bool buzzerState = false;         // Initial state of the buzzer
  bool isBuzzing = false;           // To track if the buzzing should continue
  bool stopBuzzingForever = false;  // To track if the buzzer should be stopped forever


  Notify_user();        // Constructor to initialize the buzzer
  void start_buzzer();  // Function to start the alert
  void stop_buzzer();   // Function to update the alert state
  void buzzer_loop();
};

#endif