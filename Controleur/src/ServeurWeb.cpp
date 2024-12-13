#include <Arduino.h>
#include <WebServer.h>
#include <detail/RequestHandlersImpl.h>
#include <LittleFS.h>
#include "ServeurWeb.h"

String toURI(const String &path) {
  return path;
}

ServeurWeb::ServeurWeb() {
  LittleFS.begin(true);

  pinMode(2, OUTPUT);

  this->m_webServer = new WebServer();

  this->ajouterFichiersStatiques("/");

  this->m_webServer->on("/", HTTPMethod::HTTP_GET,
                        [this]() { this->afficherRacine(); });
  this->m_webServer->on("/allumer", HTTPMethod::HTTP_GET,
                        [this]() { this->allumer(); });
  this->m_webServer->on("/eteindre", HTTPMethod::HTTP_GET,
                        [this]() { this->eteindre(); });
  this->m_webServer->onNotFound(
      [this]() { this->ressourceNonTrouvee(this->m_webServer->uri()); });

  this->m_webServer->begin();
}

void ServeurWeb::tick() { this->m_webServer->handleClient(); }

void ServeurWeb::afficherRacine() {
  Serial.println("Réception requête");
  Serial.println(this->m_webServer->uri());

  this->m_webServer->sendHeader("Location", "index.html", true);
  this->m_webServer->send(301, "text/plain", "");
}

void ServeurWeb::ajouterFichiersStatiques(String const& p_debutNomFichier) {
  File racine = LittleFS.open("/");
  ajouterFichiersStatiques(p_debutNomFichier, "", racine);
}

void ServeurWeb::ajouterFichiersStatiques(String const& p_debutNomFichier,
                                          String const& p_repertoireCourant,
                                          File& p_repertoire) {
  if (!p_repertoire) return;

  Serial.println(String("Traitement du répertoire : ") + p_repertoire.name());

  File fichier = p_repertoire.openNextFile();
  while (fichier) {
    String nomFichier = p_repertoireCourant + "/" + String(fichier.name());
    if (fichier.isDirectory()) {
      ajouterFichiersStatiques(p_debutNomFichier, p_repertoireCourant + "/" + fichier.name(), fichier);
    } else {
      if (nomFichier.startsWith(p_debutNomFichier)) {
        Serial.println(String("Ajout du fichier statique : ") + nomFichier + " pour l'URI " + toURI(nomFichier));
        this->m_webServer->serveStatic(toURI(nomFichier).c_str(), LittleFS,
                                       nomFichier.c_str());
      }
    }
    fichier.close();
    fichier = p_repertoire.openNextFile();
  }

  p_repertoire.close();
}

void ServeurWeb::ressourceNonTrouvee(const String& p_nomRessource) {
  Serial.println("Ressource '" + p_nomRessource + "' non trouvée !");
  this->m_webServer->send(404, "text/plain",
                          "Ressource '" + p_nomRessource + "' non trouvée !");
}

void ServeurWeb::allumer() {
  digitalWrite(LED_BUILTIN, HIGH);
  this->m_webServer->send(200, "application/json", "{ \"etat\": \"allumee\" }");
}

void ServeurWeb::eteindre() {
  digitalWrite(LED_BUILTIN, LOW);
  this->m_webServer->send(200, "application/json", "{ \"etat\": \"eteinte\" }");
}

