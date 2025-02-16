# IOT
IOT Project 
Fire Detection and Automatic Water Sprinkler System

Overview

This project is a fire detection and automatic water sprinkler system using an Arduino, a flame sensor, a buzzer, a water pump, and an ESP8266 WiFi module to send data to ThingSpeak for remote monitoring.

Components Used

Arduino: Main microcontroller.

Flame Sensor: Detects fire and provides digital output.

Buzzer: Alerts when fire is detected.

Water Pump: Activates automatically to extinguish fire.

ESP8266 WiFi Module: Sends sensor data to ThingSpeak.

Relay Module: Controls the water pump.

Features

Detects fire using a flame sensor.

Activates buzzer and water pump upon detection.

Sends real-time data to ThingSpeak for remote monitoring.

Uses AT commands to communicate with the ESP8266 module.

Circuit Connections

Component

Arduino Pin

Flame Sensor

D4

Buzzer

D3

Water Pump (Relay)

D5

ESP8266 RX

D12

ESP8266 TX

D13

ThingSpeak Configuration

Create a ThingSpeak account.

Create a new channel and obtain the API key.

Replace the API key in the code with your ThingSpeak API key.

Setup Instructions

Connect all components as per the circuit diagram.

Upload the provided Arduino code to your microcontroller.

Open the Serial Monitor (9600 baud rate) to view sensor readings.

Ensure WiFi credentials (SSID & Password) are correctly set in the code.

Code Explanation

Initializes ESP8266 and connects to WiFi.

Reads flame sensor input.

If fire is detected:

Buzzer is activated.

Water pump is turned ON.

Sensor data is sent to ThingSpeak.

If no fire is detected:

Buzzer and water pump remain OFF.

Data is still sent to ThingSpeak.

Author

Gowtham M G

License

This project is open-source and available for modification and distribution under the MIT License.
