#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

#include <WiFi.h>

//192.168.137.176
const char* serverAddress = "82.73.129.28";  // Raspberry Pi's IP address hardcoded
const int serverPort = 8080;                    // Servers Port Number  hardcoded
String watch_code = "998";
String full_name = "";
String phoneNumber = "";
String username = "";
String firstName = "";

class Notification_sender {
private:

  String waitForServerResponse();
  void set_information(const String &input);
  String extract_field(const String &input, const String &startField, const String &endField);

public:
  WiFiClient client;


  Notification_sender();  //constructor
  void initialize_WiFi();
  void connect_to_server();  // also send the watch_code to the server in this function
  void send_notification_to_contact_person();
  void preload_contact_phonenr();
};

#endif  // NOTIFICATION_SENDER_H