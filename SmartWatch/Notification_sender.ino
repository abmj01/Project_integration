#include "Notification_sender.h"

// Constructor
Notification_sender::Notification_sender() {
  
}

// Method to send an alert message


void Notification_sender::initialize_WiFi(){

  Serial.print("Connecting to ");  
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

 }

// At the beginnng also send "0" + " " + watch_code to the server in this function
void Notification_sender::connect_to_server(){

  if (!client.connect(serverAddress, serverPort)) {
    Serial.println("Failed to connect to server!");
    delay(100);
    return;
  }

   client.print(String("0 ") + watch_code);
   Serial.println("Watch code sent to server");
}  

// If an emergency fall is detected send the following to the server
//Send ->  "The user " + full_name + " has had a seigure in " + "coordinates: Longitude: " longitude + " " + "Latitude: " latitude

 void Notification_sender::send_notification_to_contact_person(float longitude, float latitude){

 if (client.connected()) {
    String message = "1 The user " + full_name + " has had a seizure in coordinates: Longitude: " + String(longitude, 6) + " Latitude: " + String(latitude, 6);
    client.print(message);
    Serial.println("Notification sent to contact person: " + message);
  } else {
    Serial.println("Client not connected. Failed to send notification.");
  }

}   
  
