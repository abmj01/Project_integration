#include "Battery_monitoring.h"

Battery_monitoring::Battery_monitoring(int pin) : batteryPin(pin), batteryVoltage(0.0), batteryPercentage(0.0) {
    // Initialize ADC pin
    pinMode(batteryPin, INPUT);
}

void Battery_monitoring::readBattery() {
    int adcValue = analogRead(batteryPin);

    // Calculate the battery voltage
    // If using a voltage divider, the actual battery voltage is higher than what the ADC reads
    // Multiply by (R1 + R2) / R2 to get the actual battery voltage
    batteryVoltage = (adcValue / ADC_MAX) * V_REF * (R1 + R2) / R2;

    // Map the voltage to a percentage
    batteryPercentage = ((batteryVoltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0;

    // Constrain the battery percentage between 0 and 100
    batteryPercentage = constrain(batteryPercentage, 0, 100);
}

float Battery_monitoring::getBatteryVoltage() const {
    return batteryVoltage;
}

float Battery_monitoring::getBatteryPercentage() const {
    return batteryPercentage;
}