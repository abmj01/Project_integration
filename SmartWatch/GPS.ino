#include "GPS.h"

GPS::GPS(HardwareSerial &serial) : gpsSerial(serial) {}

void GPS::begin(long baudRate) {
    gpsSerial.begin(baudRate);
}

bool GPS::available() {
    return gpsSerial.available();
}

String GPS::readData() {
    String data = "";
    while (gpsSerial.available()) {
        char c = gpsSerial.read();
        data += c;
    }

    latitude = parseData(data, "GPGGA", 2);
    longitude = parseData(data, "GPGGA", 4);
    altitude = parseData(data, "GPGGA", 9);
    speed = parseData(data, "GPVTG", 7);
    course = parseData(data, "GPVTG", 1);
    time = parseData(data, "GPRMC", 1);
    date = parseData(data, "GPRMC", 9);

    return data;
}

float GPS::getLatitude() {
    return parseFloat(latitude);
}

float GPS::getLongitude() {
    return parseFloat(longitude);
}

float GPS::getAltitude() {
    return parseFloat(altitude);
}

float GPS::getSpeed() {
    return parseFloat(speed);
}

float GPS::getCourse() {
    return parseFloat(course);
}

String GPS::getTime() {
    return time;
}

String GPS::getDate() {
    return date;
}

String GPS::parseData(String data, String identifier, int field) {
    int startIndex = data.indexOf(identifier);
    if (startIndex == -1) return "";

    int endIndex = data.indexOf('\n', startIndex);
    String line = data.substring(startIndex, endIndex);
    int commas = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') commas++;
        if (commas == field) {
            int nextComma = line.indexOf(',', i + 1);
            return line.substring(i + 1, nextComma);
        }
    }
    return "";
}

float GPS::parseFloat(String data) {
    return data.toFloat();
}
