# 🧪 Laboratory Practices - Practice 4 - Redes de sensores electrónicos

This repository contains the fourth laboratory practice for the **Redes de sensores electrónicos** course. Each section is organized in its own folder and includes the necessary files along with a brief description.
In this practice, we will be using both the Arduino Nano 33 sense BLE and an ESP32 development board to discover the possibilities of using Bluetooth and BLE as communication protocols.

## 📖 Section Overview

### 📁 Section 1 - 01_localName
📌 First working code to advertise a name on the UUID parameter (BLE protocol).  
📄 Main files:  
- `01_localName.ino`: Advertises under UUID parameter an specific provided name.

### 📁 Section 2 - 02_RGBLed
📌 Working with internal RGB LED to add check connection to board and see that you can modify parameters in order to change the color of the RGB LED.
📄 Main files:  
- `02_RGBLed.ino`: implementation to change LED color from cell phone using  Nordic BLE app.

### 📁 Section 3 - 03_acceleration
📌 Receiving values on Nordic BLE app from acceleration captured on internal sensor board.
📄 Main files:  
- `03_acceleration.ino`: Arduino file to obtain values from accelerometer on the app.  

### 📁 Section 4 - 04_activate
📌 Adds activation parameter to control accelerometer from external device.
📄 Main files:  
- `04_activate.ino`: Adds functionaliy to start / stop accelerometer from reading values of it.

### 📁 Section 5 - 05_ESP32BTSerial
📌 Creationg of a simple chat between board and BT Serial chat app.
📄 Main files:  
- `SerialToSerialBT.ino`: Reads and writes as a chat using BT serial.
