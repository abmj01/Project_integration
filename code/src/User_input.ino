#include "User_input.h"

 User_input::User_input() 
 {

 }        


 void User_input::initialize_buttons(){
  pinMode(deny_button, INPUT_PULLUP);  // use ESP internal pull up resistor
  pinMode(panic_button, INPUT_PULLUP);  
  pinMode(exercise_button, INPUT_PULLUP);  

}

 

bool User_input::long_press_panic() {
  currentState = digitalRead(panic_button); // Read the state of the switch/button

  if (lastState == HIGH && currentState == LOW) 
  { // Button is pressed
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  } else if (lastState == LOW && currentState == HIGH) 
  { // Button is released
    isPressing = false;
  }

  if (isPressing && !isLongDetected) 
  {
    long pressDuration = millis() - pressedTime;

    if (pressDuration > LONG_PRESS_TIME) {
      isLongDetected = true;
    }
  } else{
    isLongDetected = false;
  }

  lastState = currentState; // Save the last state

  return isLongDetected;
}



 bool User_input::deny_emergency_press(){
   return digitalRead(deny_button) == LOW;
 }


 bool  User_input::exercise_mode_pressed(){
   return digitalRead(exercise_button) == LOW;
 }


