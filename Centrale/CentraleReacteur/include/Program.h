#pragma once

class CoeurReacteur;
class ServeurWeb;
class DEL;

class Program {
    public:
    Program();
    void connexionReseau();
    void loop();

    private:
    ServeurWeb* m_serveurWeb;
    CoeurReacteur* m_coeurReacteur;
};