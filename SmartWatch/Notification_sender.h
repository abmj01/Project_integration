#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

#include <WiFi.h>


const char* ssid = "K9";                           //hardcoded
const char* password = "saifceo20";                // hardcoded
const char* serverAddress = "192.168.164.235";  // Raspberry Pi's IP address hardcoded
const int serverPort = 8080;                   // Servers Port Number  hardcoded
const char* watch_code = "2114";


class Notification_sender{

  private:

  public:

  char* full_name = "";

  
  Notification_sender();     //constructor

  void initialize_WiFi();

  void connect_to_server();     // also send the watch_code to the server in this function

  void send_notification_to_contact_person();   //Send ->  "The user " + full_name + " has had a siegure in " + "coordinates: Longitude: " longitude + " " + "Latitude: " latitude


};

#endif
