#pragma once
#include <Arduino.h>
#include "Task.h"


class ButtonActiverDeactiver : Task {
private:
    uint8_t m_pin;

    uint8_t m_buttonState;
    uint8_t m_lastButtonState;
    uint8_t m_lastButtonStableState;

    uint8_t m_actualTime;
    uint8_t m_lastTimeChange;
    uint8_t m_actionDelayMS;
    // plus à ajouter
public:
    ButtonActiverDeactiver( 
        uint8_t p_pin,
        uint8_t p_actionDelayMS
    );
    void tick() override;
};