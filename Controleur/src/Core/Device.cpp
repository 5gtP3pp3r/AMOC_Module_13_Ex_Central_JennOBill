#include "Core/Device.h"

#include <Wire.h>
#include <WiFi.h>

#include "Log/Logger.h"
#include "Core/StringUtil.h"

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
// Modifieé pour ignorer SimpleCollection et arduino uno.

String Device::getId() {
  uint32_t macPart = ESP.getEfuseMac() & 0xFFFFFFFF;
  return String(macPart, HEX);
}

std::vector<uint16_t> Device::getI2CAddresses() {
  byte error, address;
  std::vector<uint16_t> i2cAddresses;

  Logger.infoln(F("Scanning I2C devices..."));

  Wire.begin();
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Logger.verboseln(String(F("Sanning I2C devices at address 0x")) +
                     StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Logger.verboseln(String(F("I2C device found at address 0x")) +
                       StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
      ;

      i2cAddresses.push_back(address);
      nDevices++;
    } else if (error == 4) {
      Logger.infoln(String(F("Unknown error at address 0x")) +
                    StringUtil::padLeft(String(address, HEX), 2, '0') + F(" !"));
    }
  }
  if (nDevices == 0) {
    Logger.infoln(F("No I2C devices found."));
  } else {
    Logger.infoln(F("done."));
  }

  return i2cAddresses;
}

std::vector<WiFiNetwork> Device::getWiFiNetworks() {
  std::vector<WiFiNetwork> networks;
  WiFi.scanNetworks();
  for (int i = 0; i < WiFi.scanComplete(); i++) {
    WiFiNetwork network;
    network.ssid = WiFi.SSID(i);
    network.rssi = WiFi.RSSI(i);
    network.encryptionType = WiFi.encryptionType(i);
    network.bssid = WiFi.BSSIDstr(i);
    networks.push_back(network);
  }
  return networks;
}

