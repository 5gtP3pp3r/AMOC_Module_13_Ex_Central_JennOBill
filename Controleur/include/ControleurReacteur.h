#pragma once
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino.h>
#include "Connexion.h"
#include "config.h"

class ControleurReacteur {
private:
    String m_etatReacteur;
    String m_dernierEtat;
    String m_urlBase;
    Connexion* m_connexion;
    uint64_t m_derniereMiseAJour; 
    uint16_t m_intervalMiseAJour;    
    void getEtatReacteurAPI();
public:
    ControleurReacteur(
        Connexion* p_connexion,
        uint16_t p_intervaleMiseAJour
        );
    String getEtatReacteur() const;
    void getURL();
    void activerReacteur();
    void desactiverReacteur();
    void tick();
};