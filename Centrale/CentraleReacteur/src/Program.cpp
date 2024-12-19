#include "Program.h"
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "LED.h"
#include "ReactorHeart.h"
#include "ReactorWebServer.h"
#include "BasicCommandInterpretator/SpecificCommandInterpretator.h"
#include "BasicCommandInterpretator/Logger.h"

IPAddress ip(192,168,24,1);
IPAddress gateaway(192,168,24,1);
IPAddress mask(255,255,255,0);

const uint8_t pinDEL = 26;

Program::Program()
{
  Serial.begin(115200);
  Logger.begin(&Serial);
  this->networkConnection();
  this->m_reactorHeart = new ReactorHeart(new LED(pinDEL));
  this->m_webServer = new ReactorWebServer(this->m_reactorHeart);
  this->m_specificCommandInterpretator = new SpecificCommandInterpretator(Serial, this->m_reactorHeart);
  
}

void Program::loop()
{
  this->m_webServer->tick();
  this->m_specificCommandInterpretator->tick();
}

void Program::networkConnection()
{
  const uint8_t maxNbTries = 20;
  uint8_t nbTries = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connexion : ");
  while (nbTries < maxNbTries && WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    nbTries++;
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
   bool isSuccessfulConfig =
        WiFi.softAPConfig(ip, gateaway, mask);
    bool isSuccessfulStartup = false;
    Serial.println(String("Configuration réseau du point d'accès : ") +
                   (isSuccessfulConfig ? "Réussie" : "Échec !"));

    if (isSuccessfulConfig)
    {
      isSuccessfulStartup = WiFi.softAP(MON_AP, AP_PW);
      Serial.println(String("Démarrage du point d'accès : ") +
                     (isSuccessfulStartup ? "Réussi" : "Échec !"));

      if (isSuccessfulStartup)
      {
        Serial.print("Adresse IP du point d'accès : ");
        Serial.println(WiFi.softAPIP());
      }
    }
  }
}