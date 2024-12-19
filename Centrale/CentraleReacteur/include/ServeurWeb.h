#pragma once
#include "CoeurReacteur.h"

class WebServer;

class ServeurWeb {
    private:
    CoeurReacteur* m_coeurReacteur;
    WebServer* m_webServer;
    void handleRequetePut();
    void getStatus();
    String deserialiserRequete(String const& p_requete);
    String serialiserReponse(String const& p_reponse);
    void envoyerCors() const;
    void optionsCors() const;
    public:
    ServeurWeb(CoeurReacteur* p_coeurReacteur);
    void tick();
};