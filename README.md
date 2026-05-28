# esp32-universal-health-check
🏥 Универсальная диагностика ESP32 (C6, S3, WROOM) + гайд по настройке Arduino IDE. Модель чипа, MAC-адреса, RAM, Flash, тест пинов и LED.

🏥 ESP32 Universal Health Check + Arduino IDE setup guide. Chip model, MAC addresses, RAM, Flash, GPIO test, LED blink.
# 🏥 ESP32 Universal Health Check | Универсальная диагностика ESP32

[![ESP32](https://img.shields.io/badge/ESP32-All%20Series-000000?style=for-the-badge&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-00878F?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Version](https://img.shields.io/badge/Version-2.2-blue?style=for-the-badge)](https://github.com/Wit1974/esp32-universal-health-check)

---

## 📋 What it checks | Что проверяет

| Check | Description |
|-------|-------------|
| ✅ **Chip model** | RISC-V (C6) or Tensilica (classic) |
| ✅ **MAC addresses** | Wi-Fi + Zigbee IEEE |
| ✅ **CPU frequency & Flash size** | Real detected values |
| ✅ **Free RAM (Heap)** | Available memory |
| ✅ **Safe GPIO test** | Auto-selects pins based on model |
| ✅ **Built-in LED test** | Blinks onboard LED |

---

## 🔧 Arduino IDE Setup Guide | Настройка Arduino IDE

### 1️⃣ Install Board | Установка плат

**Path | Путь:** `File → Preferences → Additional boards manager URLs`

**Add URL:** `https://espressif.github.io`

**Install | Установка:**  
`Tools → Board → Boards Manager` → search `esp32` by `Espressif Systems` → Install (v3.0.7 or higher)

### 2️⃣ ESP32-C6 Settings (for C6 boards)

| Setting | Value |
|---------|-------|
| **Board** | ESP32C6 Dev Module |
| **USB CDC On Boot** | `Enabled` (⚠️ **MANDATORY** for Serial Monitor) |
| **Zigbee Mode** | `Zigbee Router` (if using Zigbee) |
| **Partition Scheme** | `Zigbee 4MB` |
| **Core Debug Level** | `None` |
| **Erase All Flash** | `Disabled` |

### 3️⃣ Classic ESP32 Settings (WROOM-32)

| Setting | Value |
|---------|-------|
| **Board** | ESP32 Dev Module |
| **Partition Scheme** | `Default 4MB` |

### 4️⃣ Serial Monitor Settings

| Setting | Value |
|---------|-------|
| **Baud rate** | `115200` |
| **Line ending** | `Both NL & CR` |

### 5️⃣ Super Mini Flash Trick (if upload fails)

| Step | Action |
|------|--------|
| 1 | Hold **BOOT** button |
| 2 | Press **RESET** (or reconnect USB) |
| 3 | Release **BOOT** |
| 4 | Click **Upload** |
| 5 | Press **RESET** after upload |

---

## 🚀 How to use | Как использовать

1. Download `esp32_health_check_v2.2.ino`
2. Open in Arduino IDE
3. Select your board (see settings above)
4. Click **Upload**
5. Open Serial Monitor (115200 baud)

---

## 📊 Example output | Пример вывода
