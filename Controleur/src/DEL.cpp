#include <Arduino.h>
#include "DEL.h"

DEL::DEL(const uint8_t p_pin) : m_pin(p_pin) {
  pinMode(this->m_pin, OUTPUT);
}
void DEL::allumer() const {  
  digitalWrite(this->m_pin, HIGH);  
}
void DEL::allumer(float p_intensite) const
{
  analogWrite(this->m_pin, (p_intensite * 255));
}
void DEL::eteindre() const { 
  digitalWrite(this->m_pin, LOW); 
}