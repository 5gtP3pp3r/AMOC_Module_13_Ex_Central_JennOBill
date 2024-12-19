#pragma once
#include <Arduino.h>

class LED {
private:
    uint8_t m_pin;
    
public:
    LED(const uint8_t p_pin);
    void light() const;
    void light(float p_intensity) const;
    void shut() const;
};