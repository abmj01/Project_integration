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
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 12, dateStr);  // Display the date
  u8g2.drawStr(0, 36, timeStr);  // Display the time
  u8g2.setFont(u8g2_font_ncenB12_tr); 
  u8g2.drawStr(x , y , str); // draw centered text
  display_battery_status(currentVoltage, currentPercentage);
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
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 12, dateStr);  // Display the date
  u8g2.drawStr(0, 36, timeStr);  // Display the time
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  u8g2.drawStr(x1 , y1 , str1); // draw centered text
  u8g2.drawStr(x2 , y2 , str2); // draw centered text
  display_battery_status(currentVoltage, currentPercentage);

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


void Oled_display::display_battery_status(float voltage, float percentage) {
  // Store current voltage and percentage for persistent display updates
  currentVoltage = voltage;
  currentPercentage = percentage;

  // Adjusting the size and position to be smaller and in the upper right corner
  int batteryWidth = 20;
  int batteryHeight = 10;
  int batteryX = u8g2.getDisplayWidth() - batteryWidth - 5;
  int batteryY = 5;

  // Clear only the area where the battery icon and percentage are displayed
  u8g2.setDrawColor(0); // Set draw color to black to clear
  u8g2.drawBox(batteryX - 30, batteryY - 5, 60, 20); // Clear a small area
  u8g2.setDrawColor(1); // Set draw color back to white

  // Draw the battery outline
  u8g2.drawFrame(batteryX, batteryY, batteryWidth, batteryHeight); // Outer rectangle
  u8g2.drawBox(batteryX + batteryWidth, batteryY + (batteryHeight / 4), 2, batteryHeight / 2); // Battery tip

  // Determine fill pattern based on battery percentage
  int levelWidth = (int)(percentage / 100.0 * (batteryWidth - 2)); // Width of the filled part

  // Solid fill for battery level
  u8g2.drawBox(batteryX + 1, batteryY + 1, levelWidth, batteryHeight - 2);

  // Display the percentage next to the battery icon
  char percentageStr[5];
  snprintf(percentageStr, sizeof(percentageStr), "%.0f%%", percentage);
  u8g2.setFont(u8g2_font_6x10_tr); // Smaller font
  int percentageWidth = u8g2.getStrWidth(percentageStr);
  u8g2.setCursor(batteryX - percentageWidth - 5, batteryY + batteryHeight - 1);
  u8g2.print(percentageStr);
}

 