#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>

class BatteryMonitor {
private:
    const float ADC_MAX = 4095.0;  // Maximum ADC value for ESP32
    const float V_REF = 3.3;       // Reference voltage for ADC
    const float MIN_VOLTAGE = 3.0; // Minimum battery voltage (empty)
    const float MAX_VOLTAGE = 4.2; // Maximum battery voltage (full)
    const float R1 = 10000.0;      // Value of resistor R1
    const float R2 = 10000.0;      // Value of resistor R2

    int batteryPin;                // ADC pin for battery voltage measurement
    float batteryVoltage;          // Measured battery voltage
    float batteryPercentage;       // Calculated battery percentage

public:
    BatteryMonitor(int pin);
    void readBattery();
    float getBatteryVoltage();
    float getBatteryPercentage();
};

#endif // BATTERY_MONITOR_H
