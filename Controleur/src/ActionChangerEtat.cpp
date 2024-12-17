#include "ActionChangerEtat.h"

ActionChangerEtat::ActionChangerEtat(
    ControleurReacteur* p_controleur
) :
    m_controleur(p_controleur) { ; }

void ActionChangerEtat::executer() {
    if (this->m_controleur->getEtatReacteur() == "actif") {
        this->m_controleur->desactiverReacteur();
    }
    else {
        this->m_controleur->activerReacteur();
    }
}