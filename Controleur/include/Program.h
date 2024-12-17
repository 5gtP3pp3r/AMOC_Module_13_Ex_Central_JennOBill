#pragma once
#include <Arduino.h>
#include "config.h"
#include "Program.h"
#include "ControleurReacteur.h"
#include "ActionChangerEtat.h"
#include "BoutonChangerEtat.h"
#include "SynchroniserDEL.h"
#include "Connexion.h"
#include "DEL.h"
class Program {
private:
  DEL* m_DELVerte;
  DEL* m_DELRouge;
  Connexion* m_connection;
  ActionChangerEtat* m_actionChangerEtat;
  BoutonChangerEtat* m_boutonChangerEtat;
  ControleurReacteur* m_controleurReacteur;
  SynchroniseurDEL* m_synchronoseurDEL;
  
public:
  Program();
  void loop(); 
};