#pragma once
#include <Arduino.h>

class LED{
 public:
  LED(uint8_t p_pin);

  virtual void turnOn();
  virtual void turnOff();

 private:
  uint8_t m_pin;
};
