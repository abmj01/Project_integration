#include "Oled_display.h"

 Oled_display::Oled_display(){

 }                

 void Oled_display::initialize_display(){
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
 }

 void Oled_display::clear_display(){
    display.clearDisplay();
 }

 void Oled_display::display_string(const String &str){
 

    // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(31, 31);
  display.print(str);

  // update display with all of the above graphics
  display.display();


 }