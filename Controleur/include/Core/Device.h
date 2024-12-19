#pragma once

#include <Arduino.h>

#include "Core/SimpleCollection.h"

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
#ifdef ESP32
struct WiFiNetwork {
  String ssid;
  long rssi;
  byte encryptionType;
  String bssid;
};

#include <vector>
#endif

class Device {
 public:
  static String getId();
  static SimpleCollection<uint16_t> getI2CAddresses();

#ifdef ESP32
  static std::vector<WiFiNetwork> getWiFiNetworks();
#endif
};
