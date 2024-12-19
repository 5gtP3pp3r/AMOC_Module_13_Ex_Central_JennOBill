#include "Program.h"
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "DEL.h"
#include "CoeurReacteur.h"
#include "ServeurWeb.h"
#include "BasicCommandInterpretator/InterpreteurCommandeSpecifique.h"
#include "BasicCommandInterpretator/Logger.h"

IPAddress ip(192,168,24,1);
IPAddress passerelle(192,168,24,1);
IPAddress masque(255,255,255,0);

const uint8_t pinDEL = 26;

Program::Program()
{
  Serial.begin(115200);
  Logger.begin(&Serial);
  this->connexionReseau();
  this->m_coeurReacteur = new CoeurReacteur(new DEL(pinDEL));
  this->m_serveurWeb = new ServeurWeb(this->m_coeurReacteur);
  this->m_interpreteurCommandeSpecifique = new InterpreteurCommandeSpecifique(Serial, this->m_coeurReacteur);
  
}

void Program::loop()
{
  this->m_serveurWeb->tick();
  this->m_interpreteurCommandeSpecifique->tick();
}

void Program::connexionReseau()
{
  const uint8_t nbEssaisMaximum = 20;
  uint8_t nbEssais = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connexion : ");
  while (nbEssais < nbEssaisMaximum && WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    nbEssais++;
  }
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Connecté au réseau WiFi, adresse IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("");
  }
  else
  {
   bool configReussie =
        WiFi.softAPConfig(ip, passerelle, masque);
    bool demarrageAPReussi = false;
    Serial.println(String("Configuration réseau du point d'accès : ") +
                   (configReussie ? "Réussie" : "Échec !"));

    if (configReussie)
    {
      demarrageAPReussi = WiFi.softAP(MON_AP, AP_PW);
      Serial.println(String("Démarrage du point d'accès : ") +
                     (demarrageAPReussi ? "Réussi" : "Échec !"));

      if (demarrageAPReussi)
      {
        Serial.print("Adresse IP du point d'accès : ");
        Serial.println(WiFi.softAPIP());
      }
    }
  }
}