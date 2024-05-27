#ifndef MPU_ALGO_H
#define MPU_ALGO_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

class mpu_algo{
 private:

 

 public:
 //defaut constructor
  
 mpu_algo();

 bool fall_detected = false;  //flag for fall detection
 bool exercise_mode = false;

 void initialize_mpu();                  // initialize the mpu6050
 void readFall();                        // read the sensors and detect a fall
 void exercise_mode_fall_detection();    // excersidse mode algo

};


#endif