#pragma once

#include <Arduino.h>
#include <vector>

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
// Modifieé pour ignorer SimpleCollection et arduino uno.

struct WiFiNetwork {
  String ssid;
  long rssi;
  byte encryptionType;
  String bssid;
};

class Device {
 public:
  static String getId();
  static std::vector<uint16_t> getI2CAddresses();
  static std::vector<WiFiNetwork> getWiFiNetworks();
};
