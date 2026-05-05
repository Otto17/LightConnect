/*

  LightConnect (LC_Blocking) — пример: блокирующий режим.
  Выполнение кода останавливается до закрытия портала или таймаута.

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

  Serial.println("[LC] Запуск портала (блокирующий, таймаут 2 мин)...");
  LightConnect.run(120000); // Блокируем до завершения или таймаута

  // После выхода из run() портал уже остановлен
  Serial.print("[LC] Статус: ");
  Serial.println(LightConnect.status());

  if (LightConnect.status() == LC_SUBMIT) {
    Serial.println("[LC] Данные получены:");
    Serial.print("  SSID:     "); Serial.println(lcCfg.ssid);
    Serial.print("  Pass:     "); Serial.println(lcCfg.pass);
    Serial.print("  WebLogin: "); Serial.println(lcCfg.webLogin);
    Serial.print("  WebPass:  "); Serial.println(lcCfg.webPass);
  }

  if (LightConnect.status() == LC_TIMEOUT) {
    Serial.println("[LC] Таймаут — портал закрыт автоматически.");
  }

  if (LightConnect.status() == LC_REBOOT) {
    Serial.println("[LC] Перезагрузка...");
    delay(500);
    ESP.restart();
  }
}

void loop() {
  // Основная логика программы...
}
