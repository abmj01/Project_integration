#include "Oled_display.h"

 Oled_display::Oled_display() {

 }                

 void Oled_display::initialize_display(){
    u8g2.begin();  // begin the u8g2 library
    u8g2.setContrast(255); // set display contrast/brightness
 }

 void Oled_display::initialize_ntp() {
  configTime(0, 0,  "0.nl.pool.ntp.org");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.printf("Current time: %s", asctime(&timeinfo));
}


 // str: string to be displayed
 // x : x-axis, negative value to move to left of the screen; Positive value to move the text to the right
 // y : y-axis, high or positive value to move text down; low or negative value to move text up the display
 void Oled_display::display_string(const char* str, int x, int y){

  //font size
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr); 
  u8g2.drawStr(0, 12, dateStr);  // Display the date
  u8g2.drawStr(0, 36, timeStr);  // Display the time
  u8g2.setFont(u8g2_font_ncenB12_tr); 
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
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr); 
  u8g2.drawStr(0, 12, dateStr);  // Display the date
  u8g2.drawStr(0, 36, timeStr);  // Display the time
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  u8g2.drawStr(x1 , y1 , str1); // draw centered text
  u8g2.drawStr(x2 , y2 , str2); // draw centered text
  u8g2.sendBuffer();
  
 }

void Oled_display::get_local_time(){
   struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  
  snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", timeinfo.tm_hour + 2, timeinfo.tm_min);
}

 