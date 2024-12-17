#include "ServeurWeb.h"
#include <WebServer.h>
#include <ArduinoJson.h>

ServeurWeb::ServeurWeb(CoeurReacteur* p_coeurReacteur) : m_coeurReacteur(p_coeurReacteur){
    this->m_webServer = new WebServer();

    this->m_webServer->on("/coeur-reacteur",HTTPMethod::HTTP_GET,
                          [this]() {this->getStatus();});
    this->m_webServer->on("/coeur-reacteur",HTTPMethod::HTTP_PUT,
                        [this]() {this->handleRequetePut();});
}

void ServeurWeb::tick(){
    this->m_webServer->handleClient();
}

bool ServeurWeb::getStatus(){
    return this->m_coeurReacteur->getStatut();
}

String ServeurWeb::deserialiserRequete(String const& p_requete) {
  DynamicJsonDocument doc(256);
  String resultat = "";

  DeserializationError erreur = deserializeJson(doc, p_requete);

  if (!erreur) {
    resultat = doc["etat"].as<String>();
  }

  return resultat;
}

String ServeurWeb::serialiserReponse(String const& p_reponse) {
  DynamicJsonDocument doc(256);
  char json[256];

  doc["etat"] = p_reponse;

  serializeJson(doc, json);

  return json;
}

 void ServeurWeb::handleRequetePut(){
    String requeteJson = this->m_webServer->arg("plain");
    String requete = deserialiserRequete(requeteJson);

    if(requete.isEmpty() || 
       (requete != "actif" && 
       requete!= "repos")) {
       
       this->m_webServer->send(400,"text/plain","La requrequête ne respecte pas le format.");
    }else{
        if(requete== "actif"){
            this->m_coeurReacteur->activer();
        }
        else{
            this->m_coeurReacteur->desactiver();
        }
        this->m_webServer->send(200,"text/json",serialiserReponse(requete));
    }
 }

