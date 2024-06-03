#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <Arduino.h>

// User_input class handles the user button input for long press and short press detection
class User_input {
  public:
    User_input(int pin);  // Constructor to initialize the pin
    void begin();  // Method to initialize the pin mode
    bool long_press_panic();  // Method to detect a long press (panic button)
    bool deny_emergency_press();  // Method to detect a short press (deny emergency)

  private:
    int _pin;  // Pin number where the button is connected
    unsigned long _pressStartTime;  // Variable to store the start time of the button press
    bool _isLongPress;  // Flag to indicate if a long press was detected
};

#endif // USER_INPUT_H
