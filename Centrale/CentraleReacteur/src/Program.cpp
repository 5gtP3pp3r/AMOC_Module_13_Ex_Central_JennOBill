#include "Program.h"
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "DEL.h"
#include "CoeurReacteur.h"
#include "ServeurWeb.h"

const uint8_t pinDEL = 26;

Program::Program(){
    this->m_coeurReacteur = new CoeurReacteur(new DEL(pinDEL));
    this->m_serveurWeb = new ServeurWeb(this->m_coeurReacteur);
}

void Program::loop(){
    this->m_serveurWeb->tick();
}

void Program::connexionReseau(){
    const uint8_t nbEssaisMaximum = 50;
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
    if (WiFi.softAP(MON_AP, AP_PW))
    {
      WiFi.begin(MON_AP, AP_PW);
    }
  }
}