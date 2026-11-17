
# Marine Water Cleaning Robotic Boat

## Project Prototype

![Marine Water Cleaning Robotic Boat](robotic-boat.jpg.jpeg)

*Prototype of an autonomous robotic boat designed for floating plastic waste collection in ponds and lakes.*

## Project Overview
An autonomous robotic boat designed to detect and collect floating plastic waste from ponds and lakes. The system uses an ESP32-CAM with Edge Impulse-based image classification to distinguish plastic waste from non-plastic objects and an Arduino UNO for motor control and navigation.

## Objectives
- Automate the collection of floating plastic waste.
- Identify plastic and non-plastic objects using image classification.
- Avoid obstacles using an ultrasonic sensor.
- Reduce manual effort in cleaning small water bodies.

## Hardware Components
- Arduino UNO
- ESP32-CAM with OV3660 camera
- HC-SR04 Ultrasonic Sensor
- L298N Motor Driver
- L293D Motor Driver
- DC Propulsion Motors
- Conveyor Motor
- Waste Collection Container
- Battery and Power Supply

## Software and Technologies
- Arduino IDE
- Embedded C/C++
- Edge Impulse
- Image Classification
- ESP32-CAM

## Working Principle
1. The ESP32-CAM captures images of floating objects.
2. Edge Impulse is used for plastic and non-plastic classification.
3. Plastic objects are identified for collection.
4. Non-plastic objects are ignored.
5. The Arduino UNO controls the conveyor and propulsion motors.
6. The ultrasonic sensor detects obstacles and supports collision avoidance.
7. Collected waste is stored in an onboard container.

## Project Structure
- Arduino_UNO.ino - Motor control and navigation template.
- ESP32_CAM/ESP32_CAM.ino - Edge Impulse classification integration template.

## Applications
- Pond cleaning
- Lake cleaning
- Floating plastic waste collection
- Water body maintenance

## Future Improvements
- Automatic waste-bin-full detection.
- GPS-based navigation.
- Remote monitoring and control.
- Improved object detection and classification.

## Project Domain
Embedded Systems | Robotics | IoT | Artificial Intelligence
