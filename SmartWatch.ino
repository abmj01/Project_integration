#include "User_input.h"
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
  }

  if (userButton.deny_emergency_press()) {
    Serial.println("Emergency denied.");
    // Add code to cancel the emergency here
  }

  // Monitor and display battery life
  batteryMonitor.read_battery_life();
  batteryMonitor.display_battery_life();
  
  Serial.print("Battery Life: ");
  Serial.print(batteryMonitor.get_battery_life());
  Serial.println("%");

  delay(60000); // Update battery life every minute
}
