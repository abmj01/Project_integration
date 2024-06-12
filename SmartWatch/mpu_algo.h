#ifndef MPU_ALGO_H
#define MPU_ALGO_H

// #include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


Adafruit_MPU6050 mpu;


class mpu_algo{
 private:

 const float accel_threshold = 31.00;

 public:
 //defaut constructor
  
 mpu_algo();

 const char* temperature;

 bool fall_detected = false;  //flag for fall detection

 void initialize_mpu();                  // initialize the mpu6050
 void readFall();                        // read the sensors and detect a fall
 void exercise_mode_fall_detection();    // excersidse mode algo

};


#endif