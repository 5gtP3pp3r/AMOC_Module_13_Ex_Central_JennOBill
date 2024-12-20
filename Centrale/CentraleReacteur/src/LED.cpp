#include "LED.h"

LED::LED(uint8_t p_pin)
    : m_pin(p_pin)
{
  pinMode(this->m_pin, OUTPUT);
}

void LED::turnOn()
{
  digitalWrite(this->m_pin, HIGH);
}

void LED::turnOff()
{
  digitalWrite(this->m_pin, LOW);
}
