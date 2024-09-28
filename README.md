# Pcb-dev
This repo is for PCB development

## Use NPK Sensor with ESP32
 - First connect the NPK Sensor with ESP32 using MAX485 TTL To RS485 Module as shown in the image (In Image folder).
 - Make sure the MAX485 module is properly powered. Some modules can be used on 3.3V, however, most of the modules require 5V.
 - Use a 12V / 24V DC adapter to power the NPK Sensor.
 - Add the ModbusMaster library in Arduino IDE. The ModbusMaster library used is from Doc Walker. It can be directly downloaded to Arduino IDE from Library Manager or can be accessed from "https://github.com/4-20ma/ModbusMaster".
 - Upload the code from "NPK.ino"
![alt text](Image/NPK_sensor_with_ESP32.jpg)