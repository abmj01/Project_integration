#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

#include <WiFi.h>

extern const char* ssid;
extern const char* password;
extern const char* serverAddress;
extern const int serverPort;
extern const char* watch_code;

class Notification_sender {
    String wait_for_server_response();
    void set_information(const String &input);
    String extract_field(const String &input, const String &startField, const String &endField);
public:
    WiFiClient client;
    String fullName = "";
    String username = "";
    String phoneNumber = "";

    Notification_sender();     //constructor
    void initialize_WiFi();
    void connect_to_server();  // also send the watch_code to the server in this function
    void send_notification_to_contact_person(float longitude, float latitude);   //Send ->  "The user " + full_name + " has had a siegure in " + "coordinates: Longitude: " longitude + " " + "Latitude: " latitude
};

#endif // NOTIFICATION_SENDER_H
