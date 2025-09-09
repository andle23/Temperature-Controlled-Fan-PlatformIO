# 🌡️ Temperature-Controlled Fan and Buzzer

An Arduino project that uses a **DHT11 temperature sensor** to control a **3–6V DC motor with a fan blade** and a **passive buzzer**.  The fan speed and buzzer frequency adapt to the current temperature relative to a user-set threshold (via potentiometer). The buzzer provides audible feedback with a frequency that increases as the temperature rises. Also, a 16x2 LCD that displays both the live temperature and the threshold in real time.  

---

## ✨ Features
- Temperature sensing with **DHT11**  
- Adaptive **fan speed control** using PWM (via L293D motor driver)  
- **Passive buzzer feedback** with frequency scaling based on temperature difference  
- Adjustable **temperature threshold** using potentiometer (15–30 °C)  
- **16x2 LCD** display of live temperature and threshold  
- Debugging support via Serial Monitor (optional)  

---

## 🛠️ Hardware Requirements
- Arduino Uno (or compatible)  
- DHT11 temperature sensor  
- L293D motor driver IC  
- 3–6V DC motor and fan blade 
- Passive buzzer  
- 10kΩ potentiometer  
- 16x2 LCD (16-pin) 
- 9V battery + power module (for motor supply)  
- Jumper wires and breadboard  

---

## ⚡ Wiring Notes
- Connect the LCD, 9V battery + power module, DHT11, potentiometer, DC motor with fan, passive buzzer, and L293D according to the schematic
- **Fan power (VCC2, pin 8 of L293D)** powered from external **9V supply**, not Arduino 5V rail  
- **ENA (L293D)** → Arduino **pin 9** (PWM, avoids conflict with `tone()`)  
- **Passive buzzer** → Arduino **pin 13** (works with `tone()`, no PWM required)  
- **DHT11 sensor** → pin 4  
- **Potentiometer** → A0  
- **LCD pins** → `RS=6, E=7, D4=8, D5=10, D6=11, D7=12`  
- All grounds (Arduino, L293D, power module) **must be common**  

> 📝 *Wiring colors in the schematic are for clarity only and don’t need to match your physical wires.*  

---

## 📐 Circuit Schematic
<img width="2819" height="2782" alt="Image" src="https://github.com/user-attachments/assets/c2878dee-8bd4-4b5e-8c0b-012b7a75744f" />

---

## 🎥 Demo
- [Watch Demo on YouTube](https://youtu.be/F0USRRx5Qs4)

---

## 💻 Software Setup
### PlatformIO
Add the following to your `platformio.ini`:  
```ini
lib_deps = 
    adafruit/DHT sensor library@^1.4.6
    fmalpartida/LiquidCrystal@^1.5.0
