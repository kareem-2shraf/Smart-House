# 🏡 Smart House System — Arduino-Based Environmental Automation 🌬️🚨

An Arduino-powered smart house prototype that integrates motion detection, ambient light monitoring, and temperature/humidity sensing to automate household tasks and enhance safety. This project demonstrates practical applications of embedded systems in building intelligent living environments.

---

## 📌 Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Components Required](#components-required)
4. [Circuit Diagram](#circuit-diagram)
5. [Software Requirements](#software-requirements)
6. [Installation & Setup](#installation--setup)
7. [Usage](#usage)
8. [Code Structure & Snippets](#code-structure--snippets)
9. [How It Works](#how-it-works)
10. [Project Structure](#project-structure)
11. [Team & Acknowledgements](#team--acknowledgements)

---

## 🧠 Overview

This smart house system integrates three major automation modules:

* **Motion Detection**: Enhances security by detecting movement via a PIR sensor.
* **Light Control**: Automatically manages room lighting based on ambient light using an LDR.
* **Temperature Monitoring**: Tracks temperature and humidity using the LM35 sensor.

Each module works together to simulate a responsive smart environment suitable for modern home applications.

---

## ✨ Features

* **PIR Sensor**: Detects movement and activates alarm/LED.
* **LDR Sensor**: Controls room lighting based on brightness.
* **LM35 Sensor**: Measures and displays temperature and humidity.
* **LCD I2C**: Displays the output to the user.
* **Real-time Serial Monitoring**: Displays sensor feedback.
* **Integrated Logic**: Each sensor interacts with Arduino for a seamless automation response.

---

## 🧠 Components Required

* Arduino Uno
* PIR Motion Sensor
* LDR + Resistor
* LM35 Sensor
* LED (Room Light Indicator)
* Buzzer (Motion Alarm)
* Jumper wires
* Breadboard
* PCB Board
* LCD
* Servo Motors
* Motor Drivers
* Bluetooth Module
* Keypad
---

## 🔌 Circuit Diagram

| Component                 | Arduino Pin | Description                         |
| ------------------------- | ----------- | ----------------------------------- |
| PIR Sensor                | Digital 2   | Detects human motion                |
| LDR (via voltage divider) | Analog A0   | Measures ambient light              |
| LM35 Sensor               | Digital 3   | Temperature & humidity readings     |
| Room LED Light            | Digital 5   | Lights up room based on light level |
| Buzzer                    | Digital 6   | Sounds when motion detected         |

> ⚠️ Ensure proper grounding for all components.

---

## 💻 Software Requirements

* Arduino IDE
* LCD Library
* Servo Library
---

## 🛠️ Installation & Setup

1. **Clone this repository**:

   ```bash
   git clone https://github.com/<your-username>/smart-house-system.git
   cd smart-house-system
   ```
2. **Open** `Smart_House_System.ino` using Arduino IDE.
3. **Install** the `LM35` sensor library.
4. **Wire components** as described above.
5. **Upload** the code to your Arduino Uno.
6. **Monitor** output via the Serial Monitor.

---

## ▶️ Usage

1. Place the system in a room.
2. Observe:

   * LED lights turn on/off depending on room brightness.
   * PIR sensor triggers buzzer upon movement.
   * DHT11 continuously logs environment data.
3. Adjust sensor thresholds in code if needed.

---

## 🗒️ Code Structure & Snippets

* `Smart_House_System.ino` — Main sketch with full integration logic.

### 🔧 Snippet: Motion Detection Logic

```cpp
if (digitalRead(pirPin) == HIGH) {
  digitalWrite(buzzerPin, HIGH);
  Serial.println("Motion detected!");
} else {
  digitalWrite(buzzerPin, LOW);
}
```

---

## ↺ How It Works

1. **Setup**: Initializes all sensors and pins.
2. **Loop**:
   * PIR sensor checks for motion, triggers buzzer.
   * LDR reads light level and controls LED.
   * LM35 reads temperature and humidity and logs them.
3. **Display**: All values shown via Serial Monitor.

---

## 🗂️ Project Structure

```
smart-house-system/
├── assets/
│   ├── PCB Design.png
│   ├── Mechanical Design.png
|   ├── video/
│   └── images/
├── src/
│   ├── Smart_House_System.ino
├── README.md

```

---

## 👥 Team & Acknowledgements

* **Team Member**: Kareem Ashraf, Ibrahim Mohamed, Samir El-bakary, Abdelrahman Kamal, Mohamed Anwer, Mohamed Moharam
* **Thanks To**: Arduino open-source community, mentors, and online references that helped in building and understanding this system.

---
