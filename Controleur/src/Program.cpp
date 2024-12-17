#include "Program.h"

Program::Program() { 
  this->m_DELVerte = new DEL(PIN_VERTE);
  this->m_DELRouge = new DEL(PIN_ROUGE);
  this->m_controleurReacteur = new ControleurReacteur(
    URL_API,
    INTERVAL_2
  );
  this->m_actionChangerEtat = new ActionChangerEtat(
    this->m_controleurReacteur
  );
  this->m_synchronoseurDEL = new SynchroniseurDEL(
    this->m_DELVerte,
    this->m_DELRouge,
    this->m_controleurReacteur,
    INTERVAL_1
  );
  this->m_boutonChangerEtat = new BoutonChangerEtat(
    PIN_BOUTON,
    INTERVAL_40,
    this->m_actionChangerEtat
  );
  this->m_derniereMiseAJour = DEFAUT;
  this->connexionReseau();
}

void Program::loop() {
  this->m_controleurReacteur->tick();
  this->m_boutonChangerEtat->tick();
  this->m_synchronoseurDEL->tick(); 
}

bool Program::estConnecte() {
  return (WiFi.status() == WL_CONNECTED);
} 

void Program::tick() {
  uint64_t tempsActuel = millis();
    if (tempsActuel - this->m_derniereMiseAJour >= INTERVAL_5) {
      this->m_derniereMiseAJour = tempsActuel;
      if (!estConnecte()) {
        Serial.println("Connexion perdue! Tentative de reconnexion...");
          connexionReseau();
      }
    }
}

void Program::connexionReseau() {
  
  const String ssidList[NB_RESEAUX] = { WIFI_SSID_1, WIFI_SSID_2, WIFI_SSID_3 };
  const String passwordList[NB_RESEAUX] = { WIFI_PASSWORD_1, WIFI_PASSWORD_2, WIFI_PASSWORD_3 };

  bool connecte = false;
  
   for (uint8_t reseau = 0; reseau < NB_RESEAUX && !connecte ; ++reseau){
    uint8_t nbEssais = 0;
    Serial.print("Connexion au réseau WiFi: ");
    Serial.println(ssidList[reseau]);
    WiFi.begin(ssidList[reseau], passwordList[reseau]);

    Serial.print("Connexion: [");
    while (nbEssais < NB_ESSAIS_MAX && WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("=");
      nbEssais++;
    }
    Serial.print("]");
    Serial.println("");

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Connecté au réseau WiFi: ");
      Serial.println(ssidList[reseau]);
      Serial.print("Adresse IP: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      connecte = true;
    }
    else {
      Serial.print("Échec de connexion au réseau: ");
      Serial.println(ssidList[reseau]);
    }
  }  
}
