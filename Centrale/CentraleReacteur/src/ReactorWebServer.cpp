#include "ReactorWebServer.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <uri/UriRegex.h>

ReactorWebServer::ReactorWebServer(ReactorHeart *p_reactorHeart) : m_reactorHeart(p_reactorHeart)
{
  this->m_webServer = new WebServer();

  this->m_webServer->on("/coeur-reacteur", HTTPMethod::HTTP_GET,
                        [this]()
                        { this->getState(); });
  this->m_webServer->on("/coeur-reacteur", HTTPMethod::HTTP_PUT,
                        [this]()
                        { this->handlePutRequest(); });
  this->m_webServer->on(UriRegex(".*"), HTTPMethod::HTTP_OPTIONS,
                        [this]()
                        { this->corsOptions(); });
  this->m_webServer->begin();
}

void ReactorWebServer::corsOptions() const
{
  this->m_webServer->sendHeader("Access-Control-Allow-Origin", "*");
  this->m_webServer->sendHeader("Access-Control-Max-Age", "600");
  this->m_webServer->sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  this->m_webServer->sendHeader("Access-Control-Allow-Headers", "*");
  this->m_webServer->send(204);
}

void ReactorWebServer::sendCors() const
{
  this->m_webServer->sendHeader("Access-Control-Allow-Origin", "*");
}

void ReactorWebServer::tick()
{
  this->m_webServer->handleClient();
}

void ReactorWebServer::getState()
{
  String reponse = this->m_reactorHeart->getState();
  this->m_webServer->send(200, "text/json", reponse);
}

String ReactorWebServer::deserialiseJson(String const &p_requete)
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

String ReactorWebServer::serialiseJson(String const &p_reponse)
{
  DynamicJsonDocument doc(256);
  char json[256];

  doc["etat"] = p_reponse;

  serializeJson(doc, json);

  return json;
}

void ReactorWebServer::handlePutRequest()
{
  String requeteJson = this->m_webServer->arg("plain");
  String requete = deserialiseJson(requeteJson);

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
      this->m_reactorHeart->activate();
    }
    else
    {
      this->m_reactorHeart->deactivate();
    }
    this->sendCors();
    this->m_webServer->send(200, "text/json", serialiseJson(requete));
  }
}
