#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <Arduino.h>

#define panic_button 25     // Analog Button for the deny
#define deny_button 26   // Analog Button for the deny
#define exercise_button 27      // Analog Button for the deny

class User_input{
 private:
// Panic long press button necessary variables
 const unsigned long LONG_PRESS_TIME = 3000ul; // 3000 milliseconds for a long press
 int lastState = LOW;
 unsigned long currentState;
 unsigned long pressedTime = 0ul;
 bool isPressing = false;
 bool isLongDetected = false;

// Excercise long press necessary variables
 const unsigned long DEBOUNCE_DELAY = 50; // 50 milliseconds debounce delay

 int ex_previousState = LOW; // Previous state of the exercise button
 unsigned long ex_pressedTime = 0ul; // Time when the exercise button was pressed
 bool ex_isLongDetected = false; // Flag indicating if a long press was detected



 public:
 
 bool shortPressDetected = false; // Flag indicating a short press
 bool longPressDetected = false; // Flag indicating a long press

 User_input();          // Default constructer

 
 void initialize_buttons();
 

 bool long_press_panic();             // Function to detect if the panic_button is pressed long more than 3 sec to ensure that the user might have a panic attack

 bool deny_emergency_press();         // Function to let the user deny an emergency fall by pressing the deny button

void handle_exercise_button();        // Function to handle if short press oor long press detected for the exercise mode button
};



#endif