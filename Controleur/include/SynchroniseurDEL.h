#pragma once 
#include "config.h"
#include <Arduino.h>
#include "ControleurReacteur.h"
#include "DEL.h"
#include "Task.h"

class SynchroniseurDEL : public Task {
private: 
    DEL* m_DELVerte;
    DEL* m_DELRouge;
    ControleurReacteur* m_controleur;
    uint64_t m_derniereMiseAJour; 
    uint16_t m_intervalMiseAJour;
public:
    SynchroniseurDEL(
        DEL* p_DELVerte, 
        DEL* p_DELRouge,
        ControleurReacteur* p_controleur,
        uint16_t p_intervalMiseAJour
        );
    void tick() override;
};