#pragma once

class CoeurReacteur;
class InterpreteurCommandeSpecifique;
class ServeurWeb;
class DEL;

class Program {
    public:
    Program();
    void loop();

    private:
    void connexionReseau();
    ServeurWeb* m_serveurWeb;
    CoeurReacteur* m_coeurReacteur;
    InterpreteurCommandeSpecifique* m_interpreteurCommandeSpecifique;
};