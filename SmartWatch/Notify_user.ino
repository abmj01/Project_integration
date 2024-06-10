#include "Notify_user.h"

Notify_user::Notify_user(){
    pinMode(buzzer_pin, OUTPUT); // Set the buzzer pin as an output
}

void Notify_user::start_buzzer(){
    stopBuzzingForever = false; // Allow buzzing
    startMillis = millis(); // Initialize startMillis
    isBuzzing = true; // Start the buzzing
    buzzerState = false; // Ensure initial state is off
    digitalWrite(buzzer_pin, LOW); // Ensure the buzzer is off initially
}

void Notify_user::stop_buzzer(){
    digitalWrite(buzzer_pin, LOW); // Ensure the buzzer is off
    stopBuzzingForever = true;
    isBuzzing = false; // Stop the buzzing
    startMillis = 0; // Reset startMillis to allow reinitialization
}

void Notify_user::buzzer_loop(){
    unsigned long currentMillis = millis(); 

    // Buzzer operation logic
    if (!stopBuzzingForever && isBuzzing && currentMillis - startMillis < alert_duration) {
        // Check if the interval time has passed
        if ((currentMillis - startMillis) % 1000 < 500) {
            if (!buzzerState) {
                buzzerState = true;
                digitalWrite(buzzer_pin, HIGH); // Turn on the buzzer
            }
        } else {
            if (buzzerState) {
                buzzerState = false;
                digitalWrite(buzzer_pin, LOW); // Turn off the buzzer
            }
        }
    } else if (isBuzzing) {
        stop_buzzer();
    }
}
