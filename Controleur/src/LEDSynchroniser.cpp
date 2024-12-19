#include "LEDSynchroniser.h"

LEDSynchroniser::LEDSynchroniser(
    LED* p_greenLED,
    LED* p_redLED,
    ReactorController* p_controller,
    uint16_t p_intervalUpdate
) : 
    m_greenLED(p_greenLED),
    m_redLED(p_redLED),
    m_controller(p_controller),
    m_lastUpdate(DEFAUT),
    m_intervalUpdate(p_intervalUpdate) { ; }

void LEDSynchroniser::tick() {
    uint64_t actualTime = millis();
    if (actualTime - m_lastUpdate >= this->m_intervalUpdate) {
        this->m_lastUpdate = actualTime;
        if (this->m_controller->getReactorState() == "actif") {
            this->m_greenLED->light();
            this->m_redLED->shut();
        } else {
            this->m_greenLED->shut();
            this->m_redLED->light();
        }         
    }
}
