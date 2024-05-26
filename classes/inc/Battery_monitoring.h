{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #ifndef BATTERY_MONITORING_H\
#define BATTERY_MONITORING_H\
\
#include "OLED_display.h"\
\
class Battery_monitoring \{\
  public:\
    Battery_monitoring(OLED_display &display);\
    void read_battery_life();\
    int get_battery_life();\
    void display_battery_life();\
\
  private:\
    int battery_percent;\
    OLED_display &display;\
\};\
\
#endif // BATTERY_MONITORING_H\
}