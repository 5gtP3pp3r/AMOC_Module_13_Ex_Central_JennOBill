#pragma once
#include <Arduino.h>
#include <vector>

struct WiFiNetwork
{
  String ssid;
  long rssi;
  byte encryptionType;
  String bssid;
};

class Device
{
public:
  static String getId();
  static std::vector<uint16_t> getI2CAddresses();
  static std::vector<WiFiNetwork> getWiFiNetworks();
};
