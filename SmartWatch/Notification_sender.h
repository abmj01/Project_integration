#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

#include <WiFi.h>

//192.168.137.176
const char* serverAddress = "192.168.137.176";     // Raspberry Pi's IP address hardcoded
const int serverPort = 8080;                       // Servers Port Number  hardcoded
const char* watch_code = "WZ501";
String full_name = "";

class Notification_sender {
private:

String waitForServerResponse();

public:
    WiFiClient client;
    

    Notification_sender();     //constructor
    void initialize_WiFi();
    void connect_to_server();  // also send the watch_code to the server in this function
    void send_notification_to_contact_person(float longitude, float latitude);   //Send ->  "The user " + full_name + " has had a siegure in " + "coordinates: Longitude: " longitude + " " + "Latitude: " latitude
    
};

#endif // NOTIFICATION_SENDER_H
