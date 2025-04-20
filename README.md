# 🌿 HydroGenesis – Smart IoT-Based Irrigation System with Machine Learning

**HydroGenesis** is an intelligent, sensor-driven irrigation system that automates the watering process using real-time environmental data, cloud connectivity, and machine learning. Designed with sustainability and precision agriculture in mind, the system minimizes human intervention, optimizes water usage, and supports energy-efficient control using deep sleep functionality on the ESP32 microcontroller.

---

## 🚀 Key Features

- Automated plant watering using soil moisture thresholds
- Machine learning-based irrigation prediction
- Real-time sensor monitoring on **Blynk.Console**
- Cloud-based data storage with **Firebase Realtime Database**
- Energy-saving **deep sleep mode** on ESP32
- Live status updates and user notifications

---

## 🔧 Technologies Used

### 🖥️ Software
- Arduino IDE
- Firebase Realtime Database
- Blynk.Console (web & mobile dashboard)
- Python (model training and prediction)
- Google Colab (ML development)
- Draw.io (circuit and flow diagrams)

### 🔌 Hardware
- NodeMCU ESP-32S microcontroller
- Soil Moisture Sensor
- DHT22 Temperature & Humidity Sensor
- LDR Sensor
- SR04M-2 Ultrasonic Water Level Sensor
- Relay Module
- Hi-Link HLK-PM01 5V AC-DC Converter
- 18W Submersible Water Pump

---

## 📂 Project Overview

HydroGenesis includes two major implementations:

1. **Threshold-Based Irrigation**  
   Basic ESP32 code that turns the pump ON when soil moisture is below 30% and OFF when it exceeds 70%.

2. **ML-Based Predictive Irrigation**  
   A Python-trained machine learning model uses sensor data trends to predict when the plant will need watering. ESP32 acts on the prediction and enters deep sleep between cycles for energy efficiency.

Sensor data is also uploaded to Firebase, allowing long-term tracking and cloud-based integration. The Blynk.Console interface gives real-time updates and system notifications to the user.

---

## 🧪 How It Works

- Sensors feed environmental data to the ESP32
- The system activates the water pump via a relay when needed
- Data is transmitted to both **Firebase** and **Blynk**
- The ML model analyzes trends and predicts irrigation needs
- ESP32 sleeps or wakes up based on ML output to save power

---

## 🖼️ Documentation and Media

📁 **Google Drive Folder** (thesis, diagrams, images, demo videos):  
🔗 [Open Documentation Folder](https://drive.google.com/drive/folders/16CPH9fljFklcFjaaLpkzzbaWpg-DEZUX?usp=sharing)

📘 **Thesis PDF** – includes full design, implementation, and results  
📊 **Circuit and Flow Diagrams** – created using Draw.io  
📷 **Photos & Video Demonstrations** – visual proof of working model

---

## 👨‍💻 Contributors

- **Ashish Kumar** – Core Developer, ML & IoT Integration, Hardware & Circuit Implementation, Firebase Integration, Testing & Documentation

---

## 📃 License

This project is licensed under the **GNU General Public License v3.0**.

You are free to use, modify, and redistribute this project under the terms of the GPL. Any modified or extended versions must also remain open-source under the same license.

🔗 [View Full License Text](https://www.gnu.org/licenses/gpl-3.0.en.html)

---

## 🙌 Contributing

Contributions, improvements, or adaptations for large-scale agriculture are welcome. Fork the repo, raise an issue, or open a pull request to get involved.

---

## 📫 Contact

For questions, suggestions, or collaboration:  
📧 *Contact Ashish Kumar via GitHub Issues or LinkedIn (www.linkedin.com/in/ashish-kumar-21uei009)*

---
