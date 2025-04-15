# 🌿 Hydrogensis: Smart IoT-Based Irrigation System

Hydrogensis is an advanced IoT-based smart irrigation system designed to automate plant watering and optimize resource use through real-time environmental monitoring and intelligent decision-making. Built using the **ESP32 microcontroller**, it leverages sensor data to ensure healthy plant growth with minimal user intervention. All data is visualized and monitored remotely via **Blynk.Console**, with historical data logged into **Firebase** for further analysis and machine learning integration.

---

## 🚀 Project Overview

Hydrogensis automates the irrigation process based on live sensor inputs:

- Activates the water pump when soil moisture drops below 30%.
- Turns off the pump when moisture reaches 70% to prevent overwatering.
- Monitors water tank level and sends alerts if the level is critically low.
- Tracks environmental conditions like temperature, humidity, and light intensity.
- Enables remote monitoring via Blynk mobile/web dashboards.

---

## 🔧 Hardware & Components Used

| Component               | Purpose                                      |
|------------------------|----------------------------------------------|
| **ESP32**              | Main microcontroller with Wi-Fi              |
| **Soil Moisture Sensor** | Detects moisture content in soil           |
| **DHT22 Sensor**       | Measures ambient temperature and humidity    |
| **LDR Sensor**         | Monitors ambient light intensity             |
| **SR04M-2 Ultrasonic** | Measures water tank level                    |
| **Relay Module**       | Switches water pump on/off                   |
| **Water Pump**         | Provides water to the plant as needed        |
| **Blynk.Console**      | Remote monitoring, control, and notifications |
| **Firebase**           | Logs historical sensor data for ML usage     |

---

## 🌱 Key Features

### ✅ Automated Watering Logic
- **Soil Moisture Thresholds**:
  - If moisture `< 30%`, pump turns **ON**
  - If moisture `≥ 70%`, pump turns **OFF**

- Dynamic threshold-based control to ensure optimal watering and water conservation.

### 🚰 Water Level Monitoring
- Uses **SR04M-2 Ultrasonic Sensor** to track tank water level.
- If level `< 5 cm`, an alert is sent via **Blynk app**.

### 🌡️ Environmental Monitoring
- **DHT22 Sensor** captures temperature and humidity.
- **LDR Sensor** tracks light intensity.
- All data displayed in real-time on **Blynk.Console**.

### 🔗 Remote Monitoring
- Real-time data logging and visual display on Blynk mobile/web.
- Instant notifications for critical thresholds (e.g., low water level).

---

## 🤖 Future Scope: ML Integration

- **Predictive Watering**: A machine learning model will be trained using historical data (soil moisture, temperature, humidity, light intensity) to predict:
  - When the plant will need watering next.
  - When the water tank level will drop from 30 cm to 5 cm.

- **Power Optimization**: The ESP32 will intelligently enter sleep mode during idle periods based on predictions, extending device life and saving energy.

- **Solenoid Valve**: Future versions may include solenoid valve control for improved efficiency and precise irrigation.

---

## 📁 Repository Structure

Every file and folder in this repo is meaningfully named:

