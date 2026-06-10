# Smart Agriculture Monitoring System Using IoT

## Overview
The Smart Agriculture Monitoring System is an IoT-based solution that monitors soil moisture, temperature, and humidity in real time. Using an ESP32 microcontroller, sensor data is collected and transmitted to the Ubidots cloud platform for visualization, analysis, and alert generation. The system helps farmers optimize irrigation, conserve water, and improve crop health.

## Features
- Real-time soil moisture monitoring
- Temperature and humidity tracking using DHT22
- Cloud-based data storage and visualization with Ubidots
- Wi-Fi connectivity through ESP32
- Smart alert system for:
  - Dry soil conditions
  - Overwatering risks
  - Extreme environmental conditions
- Scalable design for future automation

## Hardware Requirements
- ESP32 Development Board
- Soil Moisture Sensor
- DHT22 Temperature & Humidity Sensor
- Breadboard
- Jumper Wires

## Software Requirements
- ESP-IDF
- Ubidots Cloud Platform


## System Architecture

Sensors → ESP32 → Wi-Fi → Ubidots Cloud → Alerts

### Sensors Used
- Soil Moisture Sensor
- DHT22 Sensor

## Decision Logic

### Dry Soil Detection
- Condition: Soil Moisture > 2500
- Action: Irrigation recommended
- Alert: SMS / Call / Email

### Overwatering Risk
- Condition:
  - Soil Moisture < 1500 OR
  - Humidity > 80%
- Action: Stop irrigation
- Alert: SMS / Call

### Critical Condition
- Condition:
  - Soil Moisture > 2500
  - Humidity < 40%
  - Temperature > 35°C
- Action: Immediate irrigation required
- Alert: SMS / Call

## GPIO Connections

| Component | ESP32 Pin |
|------------|-----------|
| Soil Moisture Sensor | GPIO34 |
| DHT22 Sensor | GPIO5 |

## Communication Protocols

### Single-Wire Protocol
Used by the DHT22 sensor for temperature and humidity data transmission.

### HTTP Protocol
Used to send sensor data from ESP32 to Ubidots via REST APIs over Wi-Fi.

## Project Structure

```
├── main.c
├── soil.c
├── dht_sensor.c
├── ubidots.c
├── wifi.c
└── README.md
```

### Module Description
- `soil.c` – Reads soil moisture data
- `dht_sensor.c` – Reads temperature and humidity values
- `ubidots.c` – Handles cloud communication
- `wifi.c` – Manages Wi-Fi connectivity
- `main.c` – Integrates all modules and decision logic

## Applications
- Precision Farming
- Smart Irrigation Systems
- Greenhouse Automation
- Crop Health Monitoring
- Water Conservation

## Future Enhancements
- Automatic water pump control
- Mobile application integration
- Weather-based irrigation scheduling
- AI-based crop prediction and recommendations

## Author
**Nischal Jain H S**

## License
This project is intended for educational and research purposes.
