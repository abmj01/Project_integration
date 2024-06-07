#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

// #include <Wire.h>
#include <U8g2lib.h> 

//U8G2_SH1107_PIMORONI_128X128_2_HW_I2C u8g2;
U8G2_SH1107_PIMORONI_128X128_F_HW_I2C u8g2(U8G2_R0);



class Oled_display{
 private:
 

 //U8G2_SH1107_PIMORONI_128X128_F_HW_I2C u8g2;

 public:

 Oled_display();                // Default constructer

 void initialize_display();

 void display_string(const char* str, int x, int y);

 void display_long_string(const char* str1, const char* str2, int x1, int y1, int x2, int y2);

};


#endif