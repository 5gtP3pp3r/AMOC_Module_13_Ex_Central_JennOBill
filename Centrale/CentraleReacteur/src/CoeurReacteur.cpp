#include "CoeurReacteur.h"

CoeurReacteur::CoeurReacteur(DEL* p_del) : m_del(p_del){
    this->estActif = false;
}

void CoeurReacteur::activer(){
    this->m_del->allumer();
    this->estActif = true;
}

void CoeurReacteur::desactiver(){
    this->m_del->eteindre();
    this->estActif = false;
}

bool CoeurReacteur::getStatut(){
    return this->estActif;
}