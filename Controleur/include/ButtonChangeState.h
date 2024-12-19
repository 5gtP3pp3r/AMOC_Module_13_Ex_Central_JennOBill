#pragma once
#include "config.h"
#include <Arduino.h>
#include "ActionChangeState.h"
#include "Task.h"


class ButtonChangeState : Task {
private:
    uint8_t m_pin;
    uint8_t m_buttonState;
    uint8_t m_buttonLastState;
    uint8_t m_buttonLastStableState;
    uint8_t m_actualTime;
    uint8_t m_lastTimeChange;
    uint8_t m_actionDelayMS;
    ActionChangeState* m_actionChangeState;
public:
    ButtonChangeState( 
        uint8_t p_pin,
        uint8_t p_actionDelayMS,
        ActionChangeState* p_actionChangeState
    );
    void tick() override;
};