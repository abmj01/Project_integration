#ifndef GPS_H
#define GPS_H

#include <Arduino.h>

class GPS {
public:
    GPS(HardwareSerial &serial);
    void begin(long baudRate);
    bool available();
    String readData();
    float getLatitude();
    float getLongitude();
    float getAltitude();
    float getSpeed();
    float getCourse();
    String getTime();
    String getDate();
    
private:
    HardwareSerial &gpsSerial;
    String parseData(String data, String identifier, int field);
    float parseFloat(String data);
    String latitude, longitude, altitude, speed, course, time, date;
};

#endif
