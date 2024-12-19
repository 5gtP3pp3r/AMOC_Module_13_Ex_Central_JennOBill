#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
// Source : Williamino nino Crepeaultnino (William crepeault, partie 2 de ce travail ;-)) 


class Connection {
private:
    uint64_t m_lastUpdate; 
    uint16_t m_intervalUpdate;
    String m_url;
    bool isConnected();
public:
    Connection(
        uint16_t p_intervalUpdate
    );
    void connectToNetwork();
    String getURL();
    void tick();
};