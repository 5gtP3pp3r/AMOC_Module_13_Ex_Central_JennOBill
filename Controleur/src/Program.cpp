#include "Program.h"

Program::Program() { 
  this->m_DELVerte = new DEL(PIN_VERTE);
  this->m_DELRouge = new DEL(PIN_ROUGE);
  this->m_connexion = new Connexion(INTERVAL_5);
  this->m_controleurReacteur = new ControleurReacteur(
    this->m_connexion,
    INTERVAL_2
  );
  this->m_actionChangerEtat = new ActionChangerEtat(
    this->m_controleurReacteur
  );
  this->m_synchronoseurDEL = new SynchroniseurDEL(
    this->m_DELVerte,
    this->m_DELRouge,
    this->m_controleurReacteur,
    INTERVAL_1
  );
  this->m_boutonChangerEtat = new BoutonChangerEtat(
    PIN_BOUTON,
    INTERVAL_40,
    this->m_actionChangerEtat
  );
  this->m_connexion->connexionReseau();
  this->m_controleurReacteur->getURL();
}

void Program::loop() {
  this->m_controleurReacteur->tick();
  this->m_boutonChangerEtat->tick();
  this->m_synchronoseurDEL->tick(); 
  this->m_connexion->tick();
}
// reste à implémenter Terminal.h/cpp