#include "Tasks/ButtonChangeState.h"

ButtonChangeState::ButtonChangeState(
    uint8_t p_pin,
    uint8_t p_actionDelayMS,
    ActionChangeState* p_actionChangeState
) :
    m_pin(p_pin),
    m_actionDelayMS(p_actionDelayMS),
    m_actionChangeState(p_actionChangeState),
    m_buttonState(HIGH),
    m_buttonLastState(HIGH),
    m_buttonLastStableState(HIGH),
    m_actualTime(DEFAUT),
    m_lastTimeChange(DEFAUT) {
        pinMode(this->m_pin,INPUT);
    }

void ButtonChangeState::tick() {
    this->m_buttonState = digitalRead(this->m_pin);
    this->m_actualTime = millis();
    if (this->m_buttonState != this->m_buttonLastState) {
        this->m_lastTimeChange = this->m_actualTime;
        this->m_buttonLastState = this->m_buttonState;
    }
    if (this->m_actualTime - this->m_lastTimeChange > this->m_actionDelayMS) {
        if (this->m_buttonLastStableState == LOW && this->m_buttonState == HIGH) {
            m_actionChangeState->execute();
        }
        this->m_buttonLastStableState = this->m_buttonState;
    }
}