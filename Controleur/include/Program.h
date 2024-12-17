#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "Program.h"
#include "ControleurReacteur.h"
#include "ActionChangerEtat.h"
#include "BoutonChangerEtat.h"
#include "SynchroniserDEL.h"
#include "DEL.h"
class Program {
private:
  DEL* m_DELVerte;
  DEL* m_DELRouge;
  ActionChangerEtat* m_actionChangerEtat;
  BoutonChangerEtat* m_boutonChangerEtat;
  ControleurReacteur* m_controleurReacteur;
  SynchroniseurDEL* m_synchronoseurDEL;

  uint16_t m_derniereMiseAJour;  
  void connexionReseau();
  bool estConnecte();
  
public:
  Program();
  void loop();
  void tick();  
};