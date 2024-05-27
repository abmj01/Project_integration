#include "Notification_sender.h"

// Constructor
// Initializes the Notification_sender object.
// Currently, the constructor does not perform any specific initialization.
Notification_sender::Notification_sender() {
  // Constructor code, if needed
}

// Method to send an alert message
// This method sends an alert message using the provided GPS location and contact details.
// The method retrieves the contact information from the database retriever and sends the alert.

void Notification_sender::send_alert_message(GPS gps, int contact_person_num, String contact_person_email) {
  // Store the provided contact details and GPS object in the class instance
  this->contact_person_num = contact_person_num;
  this->contact_person_email = contact_person_email;
  this->gps_obj = gps;

  // Create an instance of the Data_base_retriever class to fetch contact information
  Data_base_retriever db_retriever;

  // Fetch the contact person's phone number from the database
  this->contact_person_num = db_retriever.fetch_contact_person_num();

  // Fetch the contact person's email address from the database
  this->contact_person_email = db_retriever.fetch_contact_person_email();

  // Send the alert message
  // The implementation of sending the alert depends on the communication method being used.
  // For example, it could send an email or an SMS message.
  
  // Print the contact details and GPS location to the Serial monitor for debugging purposes
  Serial.print("Sending alert to: ");
  Serial.print(contact_person_email);
  Serial.print(" (");
  Serial.print(contact_person_num);
  Serial.println(")");

  // Print the GPS location to the Serial monitor
  Serial.print("Location: ");
  Serial.print(gps.longitude);
  Serial.print(", ");
  Serial.println(gps.latitude);
}
  
