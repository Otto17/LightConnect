// Copyright (c) 2026 Otto
// Лицензия: MIT (см. LICENSE)

#ifndef _LightConnect_h
#define _LightConnect_h

#define LC_VERSION "1.0.0"
#define LC_AP_NAME    "LightConnect"
#define LC_AP_PASS    ""
#define LC_AP_IP      192,168,4,1
#define LC_AP_CHANNEL 1
#define LC_DNS_PORT   53
#define LC_HTTP_PORT  80

#define LC_IDLE    0
#define LC_SUBMIT  1
#define LC_REBOOT  2
#define LC_EXIT    3
#define LC_TIMEOUT 4

#include <Arduino.h>
#include <DNSServer.h>

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #define LC_WebServer ESP8266WebServer
  #define LC_AUTH_OPEN AUTH_OPEN
#else
  #include <WiFi.h>
  #include <WebServer.h>
  #define LC_WebServer WebServer
  #define LC_AUTH_OPEN WIFI_AUTH_OPEN
#endif

struct LightConnectCfg {
  char ssid[64];
  char pass[64];
  char webLogin[32];
  char webPass[32];
};

extern LightConnectCfg lcCfg;

class LightConnectClass {
public:
  void start();
  void stop();
  bool tick();
  void run(uint32_t timeout = 60000);
  byte status();
  void resetStatus();
  void setAPName(const char* name);
  void setAPPass(const char* pass);

private:
  DNSServer    _dns;
  LC_WebServer _server{LC_HTTP_PORT};
  bool  _started = false;
  byte  _status  = LC_IDLE;
  char  _apName[32];
  char  _apPass[32];

  void _setupRoutes();
  void _sendPage();
  void _handleSave();
  void _handleScan();
  void _handleReboot();
  void _handleExit();
  void _sendOk(const char* msg);
};

extern LightConnectClass LightConnect;

#endif