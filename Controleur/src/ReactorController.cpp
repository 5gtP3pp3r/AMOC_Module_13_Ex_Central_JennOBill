#include "ReactorController.h"

ReactorController::ReactorController(
    Connection* p_connection,
    uint16_t p_intervalUpdate
    ) :
        m_reactorState("inconnu"), 
        m_lastState("inconnu"),
        m_urlBase("inconnu"),
        m_connection(p_connection), 
        m_lastUpdate(DEFAUT), 
        m_intervalUpdate(p_intervalUpdate) { ; }

void ReactorController::getURL() {
    this->m_urlBase = this->m_connection->getURL();
    Serial.println(this->m_urlBase);
}

String ReactorController::getReactorState() const {
    return m_reactorState.substring(9,14);
    // StaticJsonDocument<128> document;
    // return document["etat"].as<String>();
}

void ReactorController::getReactorStateAPI() {
    HTTPClient http;
    String url = this->m_urlBase + "/coeur-reacteur";

    http.begin(url);
    int codeResponse = http.GET();

    if (codeResponse == 200) {
        this->m_reactorState = http.getString();
        if (this->m_lastState != this->m_reactorState)
        {
            Serial.println("État réacteur mis à jour : " + this->m_reactorState);
        }
        this->m_lastState = this->m_reactorState;
    } else {
        Serial.println("Erreur GET, code : " + String(codeResponse));
    }
    http.end();
}

void ReactorController::activateReactor() {
    HTTPClient http;
    String url = this->m_urlBase + "/coeur-reacteur";

    http.begin(url);
    http.addHeader("content-type", "application/json");
    int codeResponse = http.PUT("{\"etat\":\"actif\"}");

    if (codeResponse == 200) {
        this->m_reactorState = "actif";
        Serial.println("Réacteur activé.");
    } else {
        Serial.println("Erreur PUT pour activer, code : " + String(codeResponse));
    }
    http.end();
}
void ReactorController::shutReactor() {
    HTTPClient http;
    String url = m_urlBase + "/coeur-reacteur";

    http.begin(url);
    http.addHeader("content-type", "application/json");
    int codeResponse = http.PUT("{\"etat\":\"repos\"}");

    if (codeResponse == 200) {
        this->m_reactorState = "repos";
        Serial.println("Réacteur désactivé.");
    } else {
        Serial.println("Erreur PUT pour désactiver, code : " + String(codeResponse));
    }
    http.end();
}
void ReactorController::tick() {
    uint64_t actualTime = millis();
    if (actualTime - this->m_lastUpdate >= this->m_intervalUpdate) {
        this->m_lastUpdate = actualTime;
        getReactorStateAPI();
    }
}