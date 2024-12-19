#include "ReactorHeart.h"

ReactorHeart::ReactorHeart(LED *p_led) : m_led(p_led)
{
    this->isActive = false;
}

void ReactorHeart::activate()
{
    this->m_led->turnOn();
    this->isActive = true;
}

void ReactorHeart::deactivate()
{
    this->m_led->turnOff();
    this->isActive = false;
}

String ReactorHeart::getState()
{
    return this->isActive ? "{\"etat\":\"actif\"}" : "{\"etat\":\"repos\"}";
}