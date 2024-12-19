#include <Arduino.h>

#include "LED.h"

LED::LED(const uint8_t p_pin) : m_pin(p_pin) {
  pinMode(this->m_pin, OUTPUT);
}
void LED::light() const {  
  digitalWrite(this->m_pin, HIGH);  
}
void LED::light(float p_intensite) const
{
  analogWrite(this->m_pin, (p_intensite * 255));
}
void LED::shut() const { 
  digitalWrite(this->m_pin, LOW); 
}