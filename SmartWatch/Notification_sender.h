#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

<<<<<<< Updated upstream
#include "GPS.h"
#include "Data_base_retriever.h"
=======
#include <WiFi.h>

// External variables declaration
extern const char* ssid;
extern const char* password;
extern const char* serverAddress;
extern const int serverPort;
extern const char* watch_code;
>>>>>>> Stashed changes

// Notification_sender class handles sending alert messages
class Notification_sender {
  public:
    Notification_sender();  // Constructor
    void send_alert_message(GPS gps, int contact_person_num, String contact_person_email);  // Method to send alert message

<<<<<<< Updated upstream
  private:
    int contact_person_num;  // Contact person's phone number
    String contact_person_email;  // Contact person's email address
    GPS gps_obj;  // GPS object to get location data
    Data_base_retriever fetched_data_obj;  // Data base retriever object to fetch contact info
=======
    Notification_sender();     // Constructor
    void initialize_WiFi();
    void connect_to_server();  // Also send the watch_code to the server in this function
    void send_notification_to_contact_person(float longitude, float latitude);   // Send ->  "The user " + full_name + " has had a seizure in " + "coordinates: Longitude: " longitude + " " + "Latitude: " latitude
    String waitForServerResponse();
>>>>>>> Stashed changes
};

#endif // NOTIFICATION_SENDER_H
