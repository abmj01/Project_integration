# ⌚ Fall Detection Smartwatch & Medicine Reminder GPS Tracker App 

This repository contains the source code and documentation for a **Fall detection Smart Watch** that detects falls, sends alerts to a contact person through Wi-Fi, displays multiple states or choices, and displays the current time using NTP.

Additionally, it includes a **Medication Reminder Phone App** developed using the **Thunkable** platform. The app sends notifications to the user's phone to remind them to take medication at a specific time. It also features a database that allows the user to create an account, select their watch ID, and receive GPS coordinates in the event of an emergency fall.

This project is implemented on the **ESP32** microcontroller and integrates multiple advanced embedded systems concepts.

## 🔧 Key Features and Technologies
### 1. **Fall Detection**
   - The smartwatch continuously monitors accelerometer and gyroscope data from the **MPU6050** sensor to detect sudden falls.
   - When a fall is detected, the watch sends a notification to a predefined contact via Wi-Fi.

### 2. **Medication Reminder**
   - The phone app allows users to set medication reminders, which are sent as notifications to the user's device.
   - The app stores user data, including medication schedules and GPS coordinates, in a database.

### 3. **GPS Tracker**
   - In the event of a detected fall, the app sends the user's GPS location (from the phone) to the emergency contact, allowing quick response.

## 📚 Embedded Software Engineering Concepts
This project showcases advanced embedded software concepts that are highly relevant to the automotive and healthcare industries.

### 1. **FreeRTOS**
   - The system utilizes **FreeRTOS** to manage multiple tasks, such as reading sensor data, updating the display, and handling Wi-Fi communication, all running in concurrently or in parallel.
   - Tasks are designed to ensure non-blocking execution, allowing smooth real-time operation.

### 2. **Object-Oriented Programming**
   - The system is designed using **OOP principles**, making the code modular and easy to extend.
   - Separate classes are used for handling the **MPU6050 sensor**, **OLED display**, **user inputs**, and **Wi-Fi notifications**, etc..

### 3. **Non-blocking Delays with `millis()`**
   - Instead of relying on `delay()` (which can block other processes), we used **non-blocking delays** with the `millis()` function to ensure smooth operation while waiting for events like sensor data processing or OLED updates.

### 4. **Software Watchdog Timer**
   - A **software watchdog timer (WDT)** is implemented to ensure that the system resets in case of unexpected behavior, preventing lock-ups and ensuring reliability.

### 5. **Wi-Fi Connectivity**
   - The ESP32 communicates with a backend server via **Wi-Fi**, sending emergency fall notifications, user data, and medication reminders.
   - The server, hosted on a **Raspberry Pi**, processes incoming alerts and forwards them to the contact person.

### 6. **NTP (Network Time Protocol)**
   - The smartwatch displays the correct time by syncing with an NTP server over Wi-Fi.

### 7. **Real-time Notifications**
   - Notifications about falls and medication reminders are sent over **Wi-Fi** to a predefined contact, allowing for immediate response in case of emergencies.

## 📱 Phone Application (Thunkable)
   - The phone app is developed using **Thunkable**, enabling users to:
     - Set up medication reminders.
     - Create an account with a unique watch ID.
     - Receive GPS coordinates and fall alerts from the watch.
   - The app communicates with the ESP32 via Wi-Fi, retrieving real-time information such as fall alerts and medication schedules.

## 💻 Hardware Components
   - **ESP32**: The main microcontroller handling all processing.
   - **MPU6050**: Accelerometer and gyroscope sensor used for detecting falls.
   - **I2C OLED Display**: Displays real-time status, including current time, fall alerts, and other information.
   - **Input Buttons**: Allows the user to decline false falls, activate and deacrivate excersice mode.
   - **Buzzer**: Alerts the user in case of a detected fall.
   - **Raspberry Pi**: Hosts the backend server that processes notifications.
   - **Chargable Lithium Battery**: For power supply and portability.

## 🛠️ Setup and Installation
1. **ESP32 Firmware**
   - Clone this repository and upload the firmware to the ESP32 using the Arduino IDE .
   - Install libraries such as WiFi.h, Adafruit_MPU6050.h ,Adafruit_Sensor.h, U8g2lib.h, etc..
   - Ensure that the ESP32 is connected to the appropriate Wi-Fi network.

2. **Raspberry Pi Server**
   - Set up the backend server on the Raspberry Pi using the provided Python scripts.
   - The server listens for incoming notifications and forwards them to the contact person.

3. **Thunkable Phone App**
   - Install the app on your phone and register your account with the unique watch ID.
   - Set medication reminders and emergency contact details through the app.

## 🚀 Future Enhancements
- **Bluetooth Communication**: Add Bluetooth functionality to enable communication with nearby devices without needing a Wi-Fi connection.
- **Machine Learning for Fall Detection**: Use machine learning algorithms to improve the accuracy of fall detection by analyzing sensor data patterns.
- **Battery Optimization**: Implement energy-efficient power management to prolong battery life.

## 🤝 Contributions
Contributions to this project are welcome! Feel free to open an issue or submit a pull request.


