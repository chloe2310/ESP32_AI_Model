📌 Project Overview

This project focuses on building an IoT-based environmental monitoring and device control system that integrates TinyML and the MQTT communication protocol. The system is designed to collect real-time environmental data, visualize it on a cloud platform, and detect anomalies directly on embedded devices using on-device machine learning.

The monitored parameters include:

Temperature

Humidity

Ambient light intensity

The project combines both cloud-based monitoring and edge AI processing, aiming to reduce latency, save bandwidth, and improve system responsiveness.

🏗️ System Architecture

The system consists of two independent embedded nodes:
<img width="810" height="465" alt="image" src="https://github.com/user-attachments/assets/823988bb-ec8a-45df-b8f8-1a2e4b009ac4" />


1️⃣ Monitoring & Cloud Node (ESP32-DevKit-V1)

Collects sensor data from DHT11 and BH1750

Publishes data to the cloud via MQTT

Integrates with ThingsBoard for:

Real-time data visualization

Historical data storage

Remote device control (LED on/off)

<img width="847" height="441" alt="image" src="https://github.com/user-attachments/assets/84897172-bb80-43ae-9414-39d5707b475f" />


2️⃣ Edge AI Node (ESP32-S3)

Runs a TinyML anomaly detection model trained using Edge Impulse

Processes sensor data locally on the microcontroller

Detects abnormal environmental conditions in real time

Triggers a warning LED immediately when anomalies are detected

Operates independently without cloud dependency

<img width="796" height="546" alt="image" src="https://github.com/user-attachments/assets/81772094-8b0f-4557-9ca5-938dd03d7d41" />
<img width="683" height="414" alt="image" src="https://github.com/user-attachments/assets/f678caac-4fbc-4707-9ecb-c5b98c2c107f" />



🤖 Machine Learning Approach

Uses unsupervised learning (K-means clustering) for anomaly detection

The model is trained on real sensor data collected from the environment

Normal operating conditions are grouped into clusters

Data points that deviate significantly from these clusters are classified as anomalies

The trained model is deployed directly onto the ESP32-S3 for on-device inference

☁️ Communication & Platform

MQTT is used as the main communication protocol due to its lightweight and reliable publish/subscribe model

ThingsBoard serves as the IoT cloud platform for:

Device management

Data visualization dashboards

Remote control and monitoring

🎯 Key Features

Real-time environmental monitoring

Cloud-based data visualization and remote control

On-device anomaly detection using TinyML

Low latency and low power consumption

Scalable and suitable for IoT edge applications

🚀 Applications

Smart home monitoring

Smart agriculture

Environmental monitoring systems

Edge AI and embedded ML research
