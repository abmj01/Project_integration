{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include "Battery_monitoring.h"\
\
Battery_monitoring::Battery_monitoring(OLED_display &display) : display(display) \{\
  battery_percent = 100; // Assume starting with full battery\
\}\
\
void Battery_monitoring::read_battery_life() \{\
  // Read battery percentage from sensor or ADC\
  // This is a placeholder, replace with actual reading code\
  battery_percent = analogRead(A0) / 10.23; // Assuming 10-bit ADC and 100% scale\
\}\
\
int Battery_monitoring::get_battery_life() \{\
  return battery_percent;\
\}\
\
void Battery_monitoring::display_battery_life() \{\
  display.clear_display();\
  display.display_string("Battery: " + String(battery_percent) + "%");\
\}\
}