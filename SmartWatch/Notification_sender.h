#ifndef NOTIFICATION_SENDER_H
#define NOTIFICATION_SENDER_H

#include "GPS.h"
#include "Data_base_retriever.h"

// Notification_sender class handles sending alert messages
class Notification_sender {
  public:
    Notification_sender();  // Constructor
    void send_alert_message(GPS gps, int contact_person_num, String contact_person_email);  // Method to send alert message

  private:
    int contact_person_num;  // Contact person's phone number
    String contact_person_email;  // Contact person's email address
    GPS gps_obj;  // GPS object to get location data
    Data_base_retriever fetched_data_obj;  // Data base retriever object to fetch contact info
};

#endif // NOTIFICATION_SENDER_H
