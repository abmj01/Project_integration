#include "Oled_display.h"

 Oled_display::Oled_display() {

 }                

 void Oled_display::initialize_display(){
    u8g2.begin();  // begin the u8g2 library
    u8g2.setContrast(255); // set display contrast/brightness
 }

 // str: string to be displayed
 // x : x-axis, negative value to move to left of the screen; Positive value to move the text to the right
 // y : y-axis, high or positive value to move text down; low or negative value to move text up the display
 void Oled_display::display_string(const char* str, int x, int y){

  //font size
  u8g2.setFont(u8g2_font_ncenB12_tr); 
  u8g2.clearBuffer();
  u8g2.drawStr(x , y , str); // draw centered text
  u8g2.sendBuffer();

 }


 // str1 : First string to be displayed
 // str2 : Second string
 // x1 : 1st string x-axis, negative value to move to left of the screen; Positive value to move the text to the right 
 // y1 : 1st string y-axis, high or positive value to move text down; low or negative value to move text up the display
 // x2 : 2nd string x-axis, negative value to move to left of the screen; Positive value to move the text to the right 
 // y2 : 2nd string y-axis, high or positive value to move text down; low or negative value to move text up the display

 void Oled_display::display_long_string(const char* str1, const char* str2, int x1, int y1, int x2, int y2){
    //font size
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  u8g2.clearBuffer();
  u8g2.drawStr(x1 , y1 , str1); // draw centered text
  u8g2.drawStr(x2 , y2 , str2); // draw centered text
  u8g2.sendBuffer();
 }
 