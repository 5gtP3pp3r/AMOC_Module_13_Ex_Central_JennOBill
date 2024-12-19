#include "ServeurWeb.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <uri/UriRegex.h>

ServeurWeb::ServeurWeb(CoeurReacteur *p_coeurReacteur) : m_coeurReacteur(p_coeurReacteur)
{
  this->m_webServer = new WebServer();

  this->m_webServer->on("/coeur-reacteur", HTTPMethod::HTTP_GET,
                        [this]()
                        { this->getStatus(); });
  this->m_webServer->on("/coeur-reacteur", HTTPMethod::HTTP_PUT,
                        [this]()
                        { this->handleRequetePut(); });
  this->m_webServer->on(UriRegex(".*"), HTTPMethod::HTTP_OPTIONS,
                        [this]()
                        { this->optionsCors(); });
  this->m_webServer->begin();
}

void ServeurWeb::optionsCors() const
{
  this->m_webServer->sendHeader("Access-Control-Allow-Origin", "*");
  this->m_webServer->sendHeader("Access-Control-Max-Age", "600");
  this->m_webServer->sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  this->m_webServer->sendHeader("Access-Control-Allow-Headers", "*");
  this->m_webServer->send(204);
}

void ServeurWeb::envoyerCors() const
{
  this->m_webServer->sendHeader("Access-Control-Allow-Origin", "*");
}

void ServeurWeb::tick()
{
  this->m_webServer->handleClient();
}

void ServeurWeb::getStatus()
{
  String reponse = this->m_coeurReacteur->getStatut();
  this->m_webServer->send(200, "text/json", reponse);
}

String ServeurWeb::deserialiserRequete(String const &p_requete)
{
  DynamicJsonDocument doc(256);
  String resultat = "";

  DeserializationError erreur = deserializeJson(doc, p_requete);

  if (!erreur)
  {
    resultat = doc["etat"].as<String>();
  }

  return resultat;
}

String ServeurWeb::serialiserReponse(String const &p_reponse)
{
  DynamicJsonDocument doc(256);
  char json[256];

  doc["etat"] = p_reponse;

  serializeJson(doc, json);

  return json;
}

void ServeurWeb::handleRequetePut()
{
  String requeteJson = this->m_webServer->arg("plain");
  String requete = deserialiserRequete(requeteJson);

  if (requete.isEmpty() ||
      (requete != "actif" &&
       requete != "repos"))
  {

    this->m_webServer->send(400, "text/plain", "La requrequête ne respecte pas le format.");
  }
  else
  {
    if (requete == "actif")
    {
      this->m_coeurReacteur->activer();
    }
    else
    {
      this->m_coeurReacteur->desactiver();
    }
    this->envoyerCors();
    this->m_webServer->send(200, "text/json", serialiserReponse(requete));
  }
}
