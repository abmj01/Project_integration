#ifndef BATTERY_MONITORING_H
#define BATTERY_MONITORING_H

#include "OLED_display.h"

// Battery_monitoring class handles reading and displaying battery life
class Battery_monitoring {
  public:
    Battery_monitoring(OLED_display &display);  // Constructor to initialize with OLED display object
    void read_battery_life();  // Method to read battery life
    int get_battery_life();  // Method to get current battery life percentage
    void display_battery_life();  // Method to display battery life on the OLED display

  private:
    int battery_percent;  // Variable to store battery percentage
    OLED_display &display;  // Reference to the OLED display object
};

#endif // BATTERY_MONITORING_H
