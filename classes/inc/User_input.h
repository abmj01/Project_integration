{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #ifndef USER_INPUT_H\
#define USER_INPUT_H\
\
#include <Arduino.h>\
\
class User_input \{\
  public:\
    User_input(int pin);\
    void begin();\
    bool long_press_panic();\
    bool deny_emergency_press();\
\
  private:\
    int _pin;\
    unsigned long _pressStartTime;\
    bool _isLongPress;\
\};\
\
#endif // USER_INPUT_H\
}