{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include "User_input.h"\
\
User_input::User_input(int pin) \{\
  _pin = pin;\
  _pressStartTime = 0;\
  _isLongPress = false;\
\}\
\
void User_input::begin() \{\
  pinMode(_pin, INPUT);\
\}\
\
bool User_input::long_press_panic() \{\
  if (digitalRead(_pin) == HIGH) \{\
    if (_pressStartTime == 0) \{\
      _pressStartTime = millis();\
    \}\
    if (millis() - _pressStartTime > 2000) \{ // Long press duration 2 seconds\
      _isLongPress = true;\
    \}\
  \} else \{\
    _pressStartTime = 0;\
    _isLongPress = false;\
  \}\
  return _isLongPress;\
\}\
\
bool User_input::deny_emergency_press() \{\
  if (digitalRead(_pin) == HIGH && !_isLongPress) \{\
    delay(50); // Debounce delay\
    if (digitalRead(_pin) == HIGH) \{\
      return true;\
    \}\
  \}\
  return false;\
\}\
}