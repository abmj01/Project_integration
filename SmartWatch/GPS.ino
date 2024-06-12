#include "GPS.h"

GPS::GPS(HardwareSerial &serial) : gpsSerial(serial) {}

void GPS::begin(long baudRate) {
    gpsSerial.begin(baudRate);
}

bool GPS::available() {
    return gpsSerial.available();
}

void GPS::readData() {
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());
    }
}

int GPS::getSatellites() {
    return gps.satellites.value();
}

double GPS::getLatitude() {
    return gps.location.lat();
}

double GPS::getLongitude() {
    return gps.location.lng();
}

double GPS::getAltitude() {
    return gps.altitude.meters();
}

double GPS::getSpeed() {
    return gps.speed.mps();
}

int GPS::getYear() {
    return gps.date.year();
}

int GPS::getMonth() {
    return gps.date.month();
}

int GPS::getDay() {
    return gps.date.day();
}

int GPS::getHour() {
    return gps.time.hour();
}

int GPS::getMinute() {
    return gps.time.minute();
}

int GPS::getSecond() {
    return gps.time.second();
}
