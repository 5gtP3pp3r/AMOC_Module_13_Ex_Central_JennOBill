#pragma once 
#include "config.h"
#include <Arduino.h>
#include "ReactorController.h"
#include "LED.h"
#include "Task.h"

class LEDSynchroniser : public Task {
private: 
    LED* m_greenLED;
    LED* m_redLED;
    ReactorController* m_controller;
    uint64_t m_lastUpdate; 
    uint16_t m_intervalUpdate;
public:
    LEDSynchroniser(
        LED* p_greenLED, 
        LED* p_redLED,
        ReactorController* p_controller,
        uint16_t intervalUpdate
        );
    void tick() override;
};