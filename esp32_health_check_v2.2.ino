/*
 * ╔══════════════════════════════════════════════════════════╗
 * ║            🏥  ESP32 UNIVERSAL HEALTH CHECK v2.2         ║
 * ║                                                          ║
 * ║  Автор: Виталий                                          ║
 * ║  Назначение: Быстрая проверка любой ESP32 (C6, S3, WROOM)║
 * ║  Версия: 2.2 (Универсальная, русская)                    ║
 * ╚══════════════════════════════════════════════════════════╝
 * 
 * ╔══════════════════════════════════════════════════════════╗
 * ║  📋  ЧТО ПРОВЕРЯЕТ ЭТОТ СКЕТЧ:                           ║
 * ║  ✅ Модель чипа (RISC-V или Tensilica)                   ║
 * ║  ✅ MAC-адрес (Wi-Fi и Zigbee IEEE)                      ║
 * ║  ✅ Частота CPU и реальный объём Flash                   ║
 * ║  ✅ Свободная оперативная память (Heap)                  ║
 * ║  ✅ Автоподбор безопасных пинов под модель               ║
 * ║  ✅ Работа встроенного светодиода (LED)                  ║
 * ╚══════════════════════════════════════════════════════════╝
 * 
 * ╔══════════════════════════════════════════════════════════╗
 * ║  🛠️  ИНСТРУКЦИЯ (АРДУИНО ИДЕ):                           ║
 * ║  1. Плата: ESP32C6 Dev Module (или ESP32 Dev Module)    ║
 * ║  2. USB CDC On Boot: Включено (Enabled) — ВАЖНО!         ║
 * ║  3. Скорость монитора порта: 115200                      ║
 * ║  4. Если не шьется: Зажать BOOT, нажать RESET, отпустить ║
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <WiFi.h>
#include <esp_mac.h>

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n========================================");
  Serial.println("     🏥 ДИАГНОСТИКА ESP32 ЗАПУЩЕНА");
  Serial.println("========================================");

  // 1. ИНФОРМАЦИЯ О СИСТЕМЕ
  Serial.print("🔹 МОДЕЛЬ ЧИПА: ");
  Serial.print(ESP.getChipModel());
  Serial.printf(" (Ревизия v%d)\n", ESP.getChipRevision());
  Serial.printf("🔹 ЯДРА: %d | ЧАСТОТА: %d МГц\n", ESP.getChipCores(), ESP.getCpuFreqMHz());
  Serial.printf("🔹 FLASH ПАМЯТЬ: %d МБ\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("🔹 СВОБОДНО RAM: %d КБ\n", ESP.getFreeHeap() / 1024);

  // 2. ИДЕНТИФИКАЦИЯ (MAC)
  uint8_t zb_mac[8];
  Serial.print("🔹 Wi-Fi MAC:  ");
  Serial.println(WiFi.macAddress());

  if (esp_read_mac(zb_mac, ESP_MAC_IEEE802154) == ESP_OK) {
    Serial.print("🔹 Zigbee MAC: ");
    for (int i = 0; i < 8; i++) {
      Serial.printf("%02X%s", zb_mac[i], (i < 7) ? ":" : "");
    }
    Serial.println();
  }

  // 3. ТЕСТ ПИНОВ (Адаптивный список)
  Serial.println("\n🔌 ПРОВЕРКА ДОСТУПНЫХ ГНЕЗД (GPIO):");
  
  #if defined(CONFIG_IDF_TARGET_ESP32C6)
    int pins[] = {0, 1, 2, 3, 4, 5, 6, 7, 15, 18, 19, 20, 21, 22, 23};
    int led = 8; // Для Super Mini и новых DevKit
  #else
    int pins[] = {2, 4, 5, 12, 13, 14, 15, 18, 19, 21, 22, 23};
    int led = 2; // Для классики WROOM
  #endif

  int n = sizeof(pins) / sizeof(pins[0]);
  for (int i = 0; i < n; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
    delay(5);
    pinMode(pins[i], INPUT_PULLUP);
    delay(5);
    Serial.printf(" GPIO%d:%s ", pins[i], digitalRead(pins[i]) ? "✅" : "⚠️");
    if ((i + 1) % 4 == 0) Serial.println();
    pinMode(pins[i], INPUT); 
  }

  // 4. ТЕСТ СВЕТОДИОДА
  Serial.print("\n\n💡 ТЕСТ LED: Мигаю на GPIO ");
  Serial.println(led);
  pinMode(led, OUTPUT);
  for(int i=0; i<6; i++) {
    digitalWrite(led, !digitalRead(led));
    delay(200);
  }

  Serial.println("\n========================================");
  Serial.println("         ПРОВЕРКА ЗАВЕРШЕНА");
  Serial.println("========================================");
}

void loop() {}
