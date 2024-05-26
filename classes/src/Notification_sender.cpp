{\rtf1\ansi\ansicpg1252\cocoartf2761
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include "Notification_sender.h"\
\
Notification_sender::Notification_sender() \{\
  // Constructor code, if needed\
\}\
\
void Notification_sender::send_alert_message(GPS gps, int contact_person_num, String contact_person_email) \{\
  this->contact_person_num = contact_person_num;\
  this->contact_person_email = contact_person_email;\
  this->gps_obj = gps;\
\
  // Retrieve contact information\
  Data_base_retriever db_retriever;\
  this->contact_person_num = db_retriever.fetch_contact_person_num();\
  this->contact_person_email = db_retriever.fetch_contact_person_email();\
\
  // Send alert message (Implementation depends on the communication method used)\
  // For example, sending an email or SMS\
\
  Serial.print("Sending alert to: ");\
  Serial.print(contact_person_email);\
  Serial.print(" (");\
  Serial.print(contact_person_num);\
  Serial.println(")");\
\
  Serial.print("Location: ");\
  Serial.print(gps.longitude);\
  Serial.print(", ");\
  Serial.println(gps.latitude);\
  \
  // Add the code here to send the alert using the available communication module\
\}\
}