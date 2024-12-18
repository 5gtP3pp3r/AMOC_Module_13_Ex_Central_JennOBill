#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

class Connexion {
private:
    uint64_t m_derniereMiseAJour; 
    uint16_t m_intervalMiseAJour;
    String m_url;
    bool estConnecte();
public:
    Connexion(
        uint16_t p_intervalMiseAJour
    );
    void connexionReseau();
    String getURL();
    void tick();
};