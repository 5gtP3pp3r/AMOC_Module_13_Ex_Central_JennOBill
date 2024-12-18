#include "SynchroniseurDEL.h"

SynchroniseurDEL::SynchroniseurDEL(
    DEL* p_DELVerte,
    DEL* p_DELRouge,
    ControleurReacteur* p_controleur,
    uint16_t p_intervalMiseAJour
) : 
    m_DELVerte(p_DELVerte),
    m_DELRouge(p_DELRouge),
    m_controleur(p_controleur),
    m_derniereMiseAJour(DEFAUT),
    m_intervalMiseAJour(p_intervalMiseAJour) { ; }

void SynchroniseurDEL::tick() {
    uint64_t tempsActuel = millis();
    if (tempsActuel - m_derniereMiseAJour >= this->m_intervalMiseAJour) {
        this->m_derniereMiseAJour = tempsActuel;
        if (this->m_controleur->getEtatReacteur() == "actif") {
            this->m_DELVerte->allumer();
            this->m_DELRouge->eteindre();
        } else {
            this->m_DELVerte->eteindre();
            this->m_DELRouge->allumer();
        }         
    }
}
