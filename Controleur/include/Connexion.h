#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

class Connexion {
private:
    uint64_t m_derniereMiseAJour; 
    uint16_t m_intervalMiseAJour;
    bool estConnecte();
public:
    Connexion(
        uint16_t p_intervalMiseAJour
    );
    void connexionReseau();
    void tick();
};