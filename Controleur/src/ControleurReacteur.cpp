#include "ControleurReacteur.h"

ControleurReacteur::ControleurReacteur(
    Connexion* p_connexion,
    uint16_t p_intervalMiseAJour
    ) :
        m_etatReacteur("inconnu"), 
        m_dernierEtat("inconnu"),
        m_urlBase("inconnu"),
        m_connexion(p_connexion), 
        m_derniereMiseAJour(DEFAUT), 
        m_intervalMiseAJour(p_intervalMiseAJour) { ; }

void ControleurReacteur::getURL() {
    this->m_urlBase = this->m_connexion->getURL();
    Serial.println(this->m_urlBase);
}

String ControleurReacteur::getEtatReacteur() const {
    return m_etatReacteur.substring(9,14);
    // StaticJsonDocument<128> document;
    // return document["etat"].as<String>();
}

void ControleurReacteur::getEtatReacteurAPI() {
    HTTPClient http;
    String url = this->m_urlBase + "/coeur-reacteur";

    http.begin(url);
    int codeReponse = http.GET();

    if (codeReponse == 200) {
        this->m_etatReacteur = http.getString();
        if (this->m_dernierEtat != this->m_etatReacteur)
        {
            Serial.println("État réacteur mis à jour : " + this->m_etatReacteur);
        }
        this->m_dernierEtat = this->m_etatReacteur;
    } else {
        Serial.println("Erreur GET, code : " + String(codeReponse));
    }
    http.end();
}

void ControleurReacteur::activerReacteur() {
    HTTPClient http;
    String url = this->m_urlBase + "/coeur-reacteur";

    http.begin(url);
    http.addHeader("content-type", "application/json");
    int codeReponse = http.PUT("{\"etat\":\"actif\"}");

    if (codeReponse == 200) {
        this->m_etatReacteur = "actif";
        Serial.println("Réacteur activé.");
    } else {
        Serial.println("Erreur PUT pour activer, code : " + String(codeReponse));
    }
    http.end();
}
void ControleurReacteur::desactiverReacteur() {
    HTTPClient http;
    String url = m_urlBase + "/coeur-reacteur";

    http.begin(url);
    http.addHeader("content-type", "application/json");
    int codeReponse = http.PUT("{\"etat\":\"repos\"}");

    if (codeReponse == 200) {
        this->m_etatReacteur = "repos";
        Serial.println("Réacteur désactivé.");
    } else {
        Serial.println("Erreur PUT pour désactiver, code : " + String(codeReponse));
    }
    http.end();
}
void ControleurReacteur::tick() {
    uint64_t tempsActuel = millis();
    if (tempsActuel - this->m_derniereMiseAJour >= this->m_intervalMiseAJour) {
        this->m_derniereMiseAJour = tempsActuel;
        getEtatReacteurAPI();
    }
}