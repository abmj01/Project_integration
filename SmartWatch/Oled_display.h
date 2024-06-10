#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <U8g2lib.h> 

class Oled_display {
private:
  char dateStr[11];
  char timeStr[6];
  float currentVoltage;
  float currentPercentage;

public:
  Oled_display(); // Default constructor
  void initialize_display();
  void initialize_ntp();
  void display_string(const char* str, int x, int y);
  void display_long_string(const char* str1, const char* str2, int x1, int y1, int x2, int y2);
  void get_local_time();
  void display_battery_status(float voltage, float percentage, int x, int y);
};

#endif
