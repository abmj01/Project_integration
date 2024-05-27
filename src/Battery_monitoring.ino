#include "Battery_monitoring.h"

// Constructor to initialize with OLED display object
Battery_monitoring::Battery_monitoring(OLED_display &display) : display(display) {
  battery_percent = 100; // Assume starting with full battery
}

// Method to read battery life
void Battery_monitoring::read_battery_life() {
  // Read battery percentage from sensor or ADC
  // This is a placeholder, replace with actual reading code
  battery_percent = analogRead(A0) / 10.23; // Assuming 10-bit ADC and 100% scale
}

// Method to get current battery life percentage
int Battery_monitoring::get_battery_life() {
  return battery_percent;
}

// Method to display battery life on the OLED display
void Battery_monitoring::display_battery_life() {
  display.clear_display();
  display.display_string("Battery: " + String(battery_percent) + "%");
}
