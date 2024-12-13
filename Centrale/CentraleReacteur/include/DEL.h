#pragma once
#include <Arduino.h>

class DEL{
 public:
  DEL(int p_pin);

  virtual void allumer();
  virtual void eteindre();

 private:
  int m_pin;
};
