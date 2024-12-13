#pragma once
#include <Arduino.h>

class DEL {
private:
    uint8_t m_pin;
    
public:
    DEL(const uint8_t p_pin);
    void allumer() const;
    void allumer(float p_intensite) const;
    void eteindre() const;
};