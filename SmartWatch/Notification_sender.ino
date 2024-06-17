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
    String info = waitForServerResponse();
    set_information(info);
    Serial.println("Watch code sent to server, name associated: " + full_name);
  
}

// Method to send notification to the contact person
void Notification_sender::send_notification_to_contact_person() {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    String message = "1 " + phoneNumber + " " + username + " The user " + full_name + " has had a seizure, Please open the SmartGuard application to see the location.";
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

void Notification_sender::preload_contact_phonenr() {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Failed to connect to server!");
        delay(100);
        return;
    }
    String message = "2 " + watch_code;
    client.print(message);
    Serial.println("Notification sent to contact person: " + message);
    String temp = waitForServerResponse();
    if(!temp.isEmpty() && temp != phoneNumber){
      phoneNumber = temp;
      Serial.println("phoneNumber changed" + temp);
    }
    Serial.println("Server response: " + temp);
}


void Notification_sender::set_information(const String &input){
  firstName = extract_field(input, "f:", "l:");
  String lastName = extract_field(input, "l:", "p:");
  full_name = firstName + " " + lastName;
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
