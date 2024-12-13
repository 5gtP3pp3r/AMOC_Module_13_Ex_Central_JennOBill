#include "ServeurWeb.h"
#include <WebServer.h>

ServeurWeb::ServeurWeb(CoeurReacteur* p_coeurReacteur) : m_coeurReacteur(p_coeurReacteur){
    this->m_webServer = new WebServer();

    this->m_webServer->on("/coeur-reacteur",HTTPMethod::HTTP_GET,
                          [this]() {this->getStatus();});
    this->m_webServer->on("/coeur-reacteur",HTTPMethod::HTTP_PUT,
                        [this]() {this->handleRequetePut();});
}

// String json = this->m_webServer->arg("plain");
// InformationActionneur* ia = deserialiserInformationActionneur(json);

void ServeurWeb::tick(){
    this->m_webServer->handleClient();
}

bool ServeurWeb::getStatus(){
    return this->m_coeurReacteur->getStatut();
}

 void ServeurWeb::handleRequetePut(){

 }

