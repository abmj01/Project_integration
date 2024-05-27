#include "mpu_algo.h"


 mpu_algo::mpu_algo() {

 };



 void mpu_algo::initialize_mpu(){

  if (!mpu.begin()){
    Serial.println("Failed to find MPU6050 chip");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

 }


 void mpu_algo::readFall(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // calculate amplitude vector for axis
  double acceleration_magnitude = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)); // m/s

  double gyro_magnitude = sqrt(pow(g.gyro.x, 2) + pow(g.gyro.y, 2) + pow(g.gyro.z, 2));
  

  const float accel_threshold = 34.00;


  // Serial.print("Acceleration magnitude: ");
  // Serial.print(acceleration_magnitude);
  // Serial.println(" m/s");

  // Serial.print("Gyroscope magnitude: ");
  // Serial.println(gyro_magnitude);

  // if(!fall_detected)
  // Serial.println("Not yet detected");

  // Threshold values, adjust as needed
  if(acceleration_magnitude > accel_threshold){
    fall_detected = true;
  } 


  // if(fall_detected) Serial.println("Fall detected!!!!!!!!");

 }

 void mpu_algo::exercise_mode_fall_detection(){
  
 }




