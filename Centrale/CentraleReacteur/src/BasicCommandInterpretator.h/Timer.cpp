#include "BasicCommandInterpretator/Timer.h"

#include <Arduino.h>
 
Timer::Timer(unsigned long interval, Callback callback)
    : m_prochaineFois(0), m_interval(interval), m_callback(callback) {
  ;
}

void Timer::tick() {
  unsigned long tempsActuel = millis();
  if (tempsActuel >= this->m_prochaineFois) {
    while (tempsActuel >= this->m_prochaineFois ) {
      this->m_prochaineFois += this->m_interval;
    }
    this->m_callback();
  }
}
