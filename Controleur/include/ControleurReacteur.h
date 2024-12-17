#pragma once
#include "config.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino.h>

class ControleurReacteur {
private:
    const String m_urlBase;
    String m_etatReacteur;
    String m_dernierEtat;
    uint64_t m_derniereMiseAJour; 
    uint16_t m_intervalMiseAJour;    
    void getEtatReacteurAPI();
public:
    ControleurReacteur(
        const String& p_urlBase,
        uint16_t p_intervaleMiseAJour
        );
    String getEtatReacteur() const;
    void activerReacteur();
    void desactiverReacteur();
    void tick();
};