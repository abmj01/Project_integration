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


void User_input::handle_exercise_button() {

  int reading = digitalRead(exercise_button);

  shortPressDetected = false;
  longPressDetected = false;

  if (reading == LOW && ex_previousState == HIGH) { // Button was just pressed
    ex_pressedTime = millis();
  }

  if (reading == LOW && (millis() - ex_pressedTime >= 1500ul)) { // Button is being held
    if (!ex_isLongDetected) {
      Serial.println("Exercise long press detected");
      ex_isLongDetected = true;
      longPressDetected = true; // Indicate a long press
    }
  } else if (reading == HIGH && ex_previousState == LOW) { // Button was released
    if (millis() - ex_pressedTime < 1500ul) { // Short press detected
      Serial.println("Exercise short press detected");
      shortPressDetected = true; // Indicate a short press
    }
    ex_isLongDetected = false; // Reset the long press flag
  }

  ex_previousState = reading; // Save the last state
}
