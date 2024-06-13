#include "Notification_sender.h"

const char* ssid = "*";                           //hardcoded
const char* password = "*";                // hardcoded
const char* serverAddress = "*";     // Raspberry Pi's IP address hardcoded
const int serverPort = 8080;                       // Servers Port Number  hardcoded
const char* watch_code = "*";

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
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    
    client.print(String("0 ") + watch_code);
    String info = wait_for_server_response();
    set_information(info); 
    Serial.println("Watch code sent to server, name associated: " + fullName);
}

// Method to send notification to the contact person
void Notification_sender::send_notification_to_contact_person(float longitude, float latitude) {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    String message = "1 " + phoneNumber + " " + username + " The user " + fullName + " has had a seizure in coordinates: Longitude: " + String(longitude, 6) + " Latitude: " + String(latitude, 6);
    client.print(message);
    Serial.println("Notification sent to contact person: " + message);
    String output = wait_for_server_response();
    Serial.println("Server response: " + output);
}

// Private helper method to wait for server response
String Notification_sender::wait_for_server_response() {
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

void Notification_sender::set_information(const String &input){
  String firstName = extract_field(input, "f:", "l:");
  String lastName = extract_field(input, "l:", "p:");
  fullName = firstName + " " + lastName;
  phoneNumber = extract_field(input, "p:", "u:");
  username = extract_field(input, "u:", "|end|");
}

String Notification_sender::extract_field(const String &input, const String &startField, const String &endField){
  int startIndex = input.indexOf(startField);
  if (startIndex == -1) {
    return "";
  }
  
  startIndex += startField.length();
  
  int endIndex;
    endIndex = input.indexOf(endField, startIndex);
    if (endIndex == -1) {
      endIndex = input.length();
    }

  String parsedOutput = input.substring(startIndex, endIndex);
  parsedOutput.trim();
  return parsedOutput;
}
