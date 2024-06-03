#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define OLED_ADDR 0x3C     // OLED display TWI address
Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

class Oled_display{
 private:

 public:

 Oled_display();                // Default constructer

 void initialize_display();

 void clear_display();

 void display_string(const String &str);

};


#endif