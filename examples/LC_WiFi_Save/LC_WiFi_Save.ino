/*

  LightConnect (LC_WiFi_Save) — полный пример:
  Запуск портала → сохранение в память → подключение к WiFi
  
  ESP8266: использует EEPROM
  ESP32:   использует Preferences (NVS)

  Copyright (c) 2026 Otto
  Лицензия: MIT (см. LICENSE)

*/

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <EEPROM.h>
  #define USE_EEPROM
#else
  #include <WiFi.h>
  #include <Preferences.h>
  Preferences prefs;
#endif

#include <LightConnect.h>

// Размер структуры в EEPROM (для ESP8266)
#define EEPROM_SIZE sizeof(LightConnectCfg)

// Прототипы
void saveConfig();
void loadConfig();
bool connectWiFi(uint32_t timeout = 15000);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n==============================");
  Serial.println("  LightConnect полный пример");
  Serial.println("==============================\n");

  // Загружаем сохранённые настройки
  loadConfig();

  Serial.print("[CFG] SSID: ");     Serial.println(lcCfg.ssid);
  Serial.print("[CFG] WebLogin: "); Serial.println(lcCfg.webLogin);

  // Пробуем подключиться к сохранённой сети
  bool connected = false;
  if (strlen(lcCfg.ssid) > 0) {
    Serial.println("[WiFi] Подключение к сохранённой сети...");
    connected = connectWiFi();
  }

  // Если не подключились — запускаем портал
  if (!connected) {
    Serial.println("[LC] Запуск портала настройки...");
    LightConnect.setAPName("LightConnect");
    LightConnect.run(300000); // 5 минут таймаут

    switch (LightConnect.status()) {
      case LC_SUBMIT:
        Serial.println("[LC] Настройки сохранены, подключение...");
        saveConfig();
        if (connectWiFi()) {
          Serial.println("[WiFi] Подключено!");
        } else {
          Serial.println("[WiFi] Не удалось подключиться.");
        }
        break;

      case LC_REBOOT:
        Serial.println("[LC] Перезагрузка...");
        delay(300);
        ESP.restart();
        break;

      case LC_TIMEOUT:
        Serial.println("[LC] Таймаут портала.");
        break;

      case LC_EXIT:
        Serial.println("[LC] Портал закрыт.");
        break;

      default:
        break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("[WiFi] WebLogin: "); Serial.println(lcCfg.webLogin);
    Serial.print("[WiFi] WebPass:  "); Serial.println(lcCfg.webPass);
  }
}

// Сохранение конфига
void saveConfig() {
#ifdef USE_EEPROM
  EEPROM.begin(EEPROM_SIZE + 4);
  // Маркер валидности
  EEPROM.write(0, 0xAB);
  EEPROM.write(1, 0xCD);
  EEPROM.put(2, lcCfg);
  EEPROM.commit();
  EEPROM.end();
  Serial.println("[CFG] Сохранено в EEPROM.");
#else
  prefs.begin("lc", false);
  prefs.putBytes("cfg", &lcCfg, sizeof(lcCfg));
  prefs.end();
  Serial.println("[CFG] Сохранено в Preferences.");
#endif
}

// Загрузка конфига
void loadConfig() {
  memset(&lcCfg, 0, sizeof(lcCfg)); // Обнуляем структуру

#ifdef USE_EEPROM
  EEPROM.begin(EEPROM_SIZE + 4);
  uint8_t m0 = EEPROM.read(0);
  uint8_t m1 = EEPROM.read(1);
  if (m0 == 0xAB && m1 == 0xCD) {
    EEPROM.get(2, lcCfg);
    Serial.println("[CFG] Загружено из EEPROM.");
  } else {
    Serial.println("[CFG] EEPROM пуста, используем defaults.");
  }
  EEPROM.end();
#else
  prefs.begin("lc", true);
  if (prefs.isKey("cfg")) {
    prefs.getBytes("cfg", &lcCfg, sizeof(lcCfg));
    Serial.println("[CFG] Загружено из Preferences.");
  } else {
    Serial.println("[CFG] Preferences пуста, используем defaults.");
  }
  prefs.end();
#endif
}

// Подключение к WiFi
bool connectWiFi(uint32_t timeout) {
  if (strlen(lcCfg.ssid) == 0) return false;

  WiFi.mode(WIFI_STA);
  WiFi.begin(lcCfg.ssid, lcCfg.pass);

  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start >= timeout) return false;
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  return true;
}

void loop() {
  // Основная логика программы...
}
