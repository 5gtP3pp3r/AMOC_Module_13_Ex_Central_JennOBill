#include "DEL.h"

DEL::DEL(int p_pin)
    :m_pin(p_pin) {
  pinMode(this->m_pin, OUTPUT);
}

void DEL::allumer() {
  digitalWrite(this->m_pin, HIGH);
}

void DEL::eteindre() {
  digitalWrite(this->m_pin, LOW);
}

