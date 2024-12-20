#pragma once
#include "LED.h"

class ReactorHeart
{
private:
    bool isActive;
    LED *m_led;

public:
    ReactorHeart(LED *p_led);
    void activate();
    void deactivate();
    String getState();
};