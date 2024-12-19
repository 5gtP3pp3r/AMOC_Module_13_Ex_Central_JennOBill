#pragma once
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Connection.h"
#include "config.h"

class ReactorController {
private:
    String m_reactorState;
    String m_lastState;
    String m_urlBase;
    Connection* m_connection;
    uint64_t m_lastUpdate; 
    uint16_t m_intervalUpdate;    
    void getReactorStateAPI();
public:
    ReactorController(
        Connection* p_connection,
        uint16_t p_m_intervalUpdate
        );
    String getReactorState() const;
    void getURL();
    void activateReactor();
    void shutReactor();
    void tick();
};