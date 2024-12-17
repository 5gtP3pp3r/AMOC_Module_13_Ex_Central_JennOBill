#pragma once
#include <Arduino.h>

class DEL{
 public:
  DEL(uint8_t p_pin);

  virtual void allumer();
  virtual void eteindre();

 private:
  uint8_t m_pin;
};
