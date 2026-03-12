# ESP32 MPU6050 Drone Orientation Simulator using Processing

![Python](https://img.shields.io/badge/Python-3.10+-blue)
![Machine Learning](https://img.shields.io/badge/Machine%20Learning-Classification-green)
![Scikit-Learn](https://img.shields.io/badge/Scikit--Learn-ML-orange)
![XGBoost](https://img.shields.io/badge/XGBoost-Boosting-red)
![Streamlit](https://img.shields.io/badge/Streamlit-Deployed-success)

## Overview

This project demonstrates a **real-time drone orientation visualization system** using an ESP32 microcontroller and an MPU6050 inertial measurement unit (IMU) sensor. The system reads motion data from the IMU, calculates orientation angles such as **Pitch, Roll, and Yaw**, and transmits these values through serial communication to the **Processing IDE**, where a **3D drone model simulates the motion** in real time.

The goal of this project is to provide a clear understanding of how **motion sensing, embedded systems, and real-time visualization** work together in applications such as drones, robotics, and stabilization systems.

## Hardware Components

* ESP32 Microcontroller
* MPU6050 Gyroscope + Accelerometer Sensor
* Jumper Wires
* USB Cable

## Software Requirements

* Arduino IDE
* Processing IDE
* ESP32 Board Package

## Working Principle

The **MPU6050 sensor** integrates a **3-axis accelerometer and a 3-axis gyroscope** to measure motion and rotation.

* The accelerometer measures **linear acceleration** along the X, Y, and Z axes.
* The gyroscope measures **angular velocity** around these axes.

The ESP32 reads this data through the **I2C communication protocol**, processes it, and calculates the orientation angles **Pitch, Roll, and Yaw**.

These values are then sent to the computer using **serial communication**.

On the computer side, the **Processing IDE** reads the serial data and updates a **3D drone model** accordingly. When the MPU6050 sensor is physically tilted or rotated, the drone model in the Processing window rotates in the same direction, creating a real-time orientation simulator.

## Key Features

* Real-time **Pitch, Roll, and Yaw calculation**
* Serial communication between **ESP32 and Processing**
* **3D drone visualization** based on sensor orientation
* Interactive demonstration of drone attitude control
* Easy-to-understand project for learning IMU sensors

## Applications

* Drone flight stabilization systems
* Robotics orientation tracking
* Camera gimbal stabilization
* Motion-controlled interfaces
* Virtual reality and gesture systems

## Learning Outcomes

* Interfacing **MPU6050 with ESP32**
* Understanding IMU sensor working principles
* Calculating orientation angles from sensor data
* Serial communication between hardware and software
* Real-time **3D visualization using Processing**

## Future Improvements

* Implement **sensor fusion algorithms** (Complementary Filter / Kalman Filter)
* Improve the **3D drone graphics**
* Add **wireless data transmission using Wi-Fi**
* Extend the system for **drone flight control experiments**

## Credits

This project was inspired by and adapted from the following source:

* Original Concept / Reference: *ESP32 MPU6050 Drone Orientation Simulation*
* Credit Link: https://github.com/

Special thanks to the open-source community for providing resources and inspiration for embedded systems and visualization projects.
