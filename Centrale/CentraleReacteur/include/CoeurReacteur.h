#pragma once
#include "DEL.h"

class CoeurReacteur
{
    private:
    bool estActif;
    DEL* m_del;

    public:
    CoeurReacteur(DEL* p_del);
    void activer();
    void desactiver();
    String getStatut();
};