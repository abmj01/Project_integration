#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <HardwareSerial.h>

class GPS {
public:
    GPS(HardwareSerial &serial);
    void begin(long baudRate);
    bool available();
    void readData();
    int getSatellites();
    double getLatitude();
    double getLongitude();
    double getAltitude();
    double getSpeed();
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();
    
private:
    HardwareSerial &gpsSerial;
    TinyGPSPlus gps;
};

#endif
