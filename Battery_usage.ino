#include <TFT_eSPI.h>  // Include the graphics library (this includes the Adafruit_GFX library)
#include "driver/gpio.h"  // Include the ESP-IDF GPIO header

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();

// ADC pin for battery voltage measurement
#define BATTERY_PIN 34  // Replace with the correct pin number for your board

// ADC and voltage reference
const float ADC_MAX = 4095.0; // Maximum ADC value for ESP32
const float V_REF = 3.3; // Reference voltage for ADC

// Battery voltage range
const float MIN_VOLTAGE = 3.0; // Minimum battery voltage (empty)
const float MAX_VOLTAGE = 4.2; // Maximum battery voltage (full)

// Voltage divider values (if used)
const float R1 = 10000.0; // Value of resistor R1
const float R2 = 10000.0; // Value of resistor R2

void setup() {
  // Initialize the serial port
  Serial.begin(115200);
  
  // Initialize the TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
}

void loop() {
  // Read the ADC value
  int adcValue = analogRead(BATTERY_PIN);
  
  // Calculate the battery voltage
  // If using a voltage divider, the actual battery voltage is higher than what the ADC reads
  // Multiply by (R1 + R2) / R2 to get the actual battery voltage
  float batteryVoltage = (adcValue / ADC_MAX) * V_REF * (R1 + R2) / R2;
  
  // Map the voltage to a percentage
  float batteryPercentage = ((batteryVoltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0;
  
  // Constrain the battery percentage between 0 and 100
  batteryPercentage = constrain(batteryPercentage, 0, 100);

  // Clear the display
  tft.fillScreen(TFT_BLACK);

  // Print the battery voltage
  tft.setCursor(10, 40);
  tft.printf("Voltage: %.2f V", batteryVoltage);

  // Print the battery percentage
  tft.setCursor(10, 80);
  tft.printf("Battery: %.0f %%", batteryPercentage);

  // Draw a battery icon with the percentage
  tft.drawRect(10, 120, 100, 20, TFT_WHITE);
  tft.fillRect(11, 121, (int)(batteryPercentage), 18, TFT_GREEN);
  tft.setCursor(120, 120);
  tft.printf("%.0f %%", batteryPercentage);

  // Delay for a second
  delay(1000);
}
