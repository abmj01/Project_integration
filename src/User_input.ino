#include "User_input.h"

// Constructor to initialize the pin
User_input::User_input(int pin) {
  _pin = pin;
  _pressStartTime = 0;
  _isLongPress = false;
}

// Method to initialize the pin mode
void User_input::begin() {
  pinMode(_pin, INPUT);
}

// Method to detect a long press (panic button)
bool User_input::long_press_panic() {
  if (digitalRead(_pin) == HIGH) {
    if (_pressStartTime == 0) {
      _pressStartTime = millis();
    }
    if (millis() - _pressStartTime > 2000) { // Long press duration 2 seconds
      _isLongPress = true;
    }
  } else {
    _pressStartTime = 0;
    _isLongPress = false;
  }
  return _isLongPress;
}

// Method to detect a short press (deny emergency)
bool User_input::deny_emergency_press() {
  if (digitalRead(_pin) == HIGH && !_isLongPress) {
    delay(50); // Debounce delay
    if (digitalRead(_pin) == HIGH) {
      return true;
    }
  }
  return false;
}
