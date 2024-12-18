#include "Connexion.h"

Connexion::Connexion( 
    uint16_t p_intervalMiseAJour
) :
    m_derniereMiseAJour(DEFAUT),
    m_intervalMiseAJour(p_intervalMiseAJour),
    m_url("inconnu") { ; }

bool Connexion::estConnecte() {
  return (WiFi.status() == WL_CONNECTED);
}

String Connexion::getURL() {
    return this->m_url;
}

void Connexion::tick() {
  uint64_t tempsActuel = millis();
    if (tempsActuel - this->m_derniereMiseAJour >= this->m_intervalMiseAJour) {
      this->m_derniereMiseAJour = tempsActuel;
      if (!estConnecte()) {
        Serial.println("Connexion perdue! Tentative de reconnexion...");
          connexionReseau();
      }
    }
}

void Connexion::connexionReseau() {

  bool connecte = false;
  
   for (uint8_t reseau = 0; reseau < NB_RESEAUX && !connecte ; ++reseau){
    uint8_t nbEssais = 0;
    Serial.print("Connexion au réseau WiFi: ");
    Serial.println(ssidListe[reseau]);
    WiFi.begin(ssidListe[reseau], passwordListe[reseau]);

    Serial.print("Connexion: [");
    while (nbEssais < NB_ESSAIS_MAX && WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("=");
      nbEssais++;
    }
    Serial.print("]");
    Serial.println("");

    if (WiFi.status() == WL_CONNECTED) {
      this->m_url = urlListe[reseau];
      Serial.print("Connecté au réseau WiFi: ");
      Serial.println(ssidListe[reseau]);
      Serial.print("Adresse IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      connecte = true;
    }
    else {
      Serial.print("Échec de connexion au réseau: ");
      Serial.println(ssidListe[reseau]);
    }
  }  
}
