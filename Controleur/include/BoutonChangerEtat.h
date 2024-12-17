#pragma once
#include "config.h"
#include <Arduino.h>
#include "ActionChangerEtat.h"
#include "Task.h"


class BoutonChangerEtat : Task {
private:
    uint8_t m_pin;
    uint8_t m_etatBouton;
    uint8_t m_dernierEtatBouton;
    uint8_t m_dernierEtatStable;
    uint8_t m_tempsActuel;
    uint8_t m_dernierChangementTemps;
    uint8_t m_delaiActionMS;
    ActionChangerEtat* m_actionChangerEtat;
public:
    BoutonChangerEtat( 
        uint8_t p_pin,
        uint8_t p_delaiActionMS,
        ActionChangerEtat* p_actionChangerEtat
    );
    void tick() override;
};