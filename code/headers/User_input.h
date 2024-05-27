#ifndef USER_INPUT_H
#define USER_INPUT_H

#define panic_button 15     // Analog Button for the deny
#define deny_button 2    // Analog Button for the deny
#define exercise_button 13      // Analog Button for the deny

class User_input{
 private:

 const unsigned long LONG_PRESS_TIME = 3000ul; // 3000 milliseconds for a long press
 int lastState = LOW;
 unsigned long currentState;
 unsigned long pressedTime = 0ul;
 bool isPressing = false;
 bool isLongDetected = false;

 public:

 User_input();          //Default constructer

 
 void initialize_buttons();
 

 bool long_press_panic();           // Function to detect if the panic_button is pressed long more than 3 sec to ensure that the user might have a panic attack

 bool deny_emergency_press();       // Function to let the user deny an emergency fall by pressing the deny button

 bool exercise_mode_pressed();      // Function to detect if the exercise button is pressed


};



#endif