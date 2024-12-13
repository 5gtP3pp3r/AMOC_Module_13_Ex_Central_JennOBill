#include "CoeurReacteur.h"

class WebServer;

class ServeurWeb {
    private:
    CoeurReacteur* m_coeurReacteur;
    WebServer* m_webServer;

    public:
    ServeurWeb(CoeurReacteur* p_coeurReacteur);
    void tick();
    bool getStatus();
    void handleRequetePut();
    String deserialiserRequete(String const& p_requete);
    String serialiserReponse(String p_reponse);
};