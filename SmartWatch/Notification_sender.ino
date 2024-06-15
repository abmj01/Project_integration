#include "Notification_sender.h"


// Constructor
Notification_sender::Notification_sender() {
}

// Method to initialize WiFi
void Notification_sender::initialize_WiFi() {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

// Method to connect to the server and send the initial message
void Notification_sender::connect_to_server() {
    Serial.print("*");

    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    
    client.print(String("0 ") + watch_code);
    full_name = waitForServerResponse();
    Serial.println("Watch code sent to server, name associated: " + full_name);
  
}

// Method to send notification to the contact person
void Notification_sender::send_notification_to_contact_person(float longitude, float latitude) {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    String message = "1 The user " + full_name + " has had a seizure in coordinates: Longitude: " + String(longitude, 6) + " Latitude: " + String(latitude, 6);
    client.print(message);
    Serial.println("Notification sent to contact person: " + message);
    String output = waitForServerResponse();
    Serial.println("Server response: " + output);
}

// Private helper method to wait for server response
String Notification_sender::waitForServerResponse() {
    unsigned long timeout = millis() + 5000; // 5 seconds timeout
    while (!client.available() && millis() < timeout) {
        delay(100);
    }

    if (client.available()) {
        // Receive response from server
        String response = client.readStringUntil('\n');
        return response;
    } else {
        return "Timeout waiting for server response";
    }
}
