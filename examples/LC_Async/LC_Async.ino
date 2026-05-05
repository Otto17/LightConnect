/*

  LightConnect (LC_Async) — пример: неблокирующий режим.
  Портал работает в фоне, loop() свободен.

  Copyright (c) 2026 Otto
  Лицензия: MIT (см. LICENSE)

*/

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else
  #include <WiFi.h>
#endif

#include <LightConnect.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n[LC] Запуск портала...");

  // Опционально: задать своё имя AP перед стартом
  // LightConnect.setAPName("MyDevice Setup");

  LightConnect.start(); // Запускаем портал (неблокирующий)
}

void loop() {
  // Вызываем tick() — возвращает true, когда портал завершил работу
  if (LightConnect.tick()) {

    Serial.print("[LC] Статус: ");
    Serial.println(LightConnect.status());

    switch (LightConnect.status()) {

      case LC_SUBMIT:
        Serial.println("[LC] Настройки сохранены!");
        Serial.print("  SSID:     "); Serial.println(lcCfg.ssid);
        Serial.print("  Pass:     "); Serial.println(lcCfg.pass);
        Serial.print("  WebLogin: "); Serial.println(lcCfg.webLogin);
        Serial.print("  WebPass:  "); Serial.println(lcCfg.webPass);
        // Здесь: нужно сохранить данные в EEPROM/Preferences, подключиться к WiFi...
        break;

      case LC_REBOOT:
        Serial.println("[LC] Перезагрузка по запросу из WEB...");
        delay(500);
        ESP.restart();
        break;

      case LC_EXIT:
        Serial.println("[LC] Портал закрыт вручную.");
        break;

      default:
        break;
    }
  }

  // Здесь выполняется остальная логика проекта...
}
