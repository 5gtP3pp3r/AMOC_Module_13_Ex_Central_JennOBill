#pragma once

#include "BasicCommandInterpretor.h"
#include "CoeurReacteur.h"

class InterpreteurCommandeSpecifique : public BasicCommandInterpretor {
 protected:
  virtual bool interpret(const String &commande,
                         const String &parametres) override;
  virtual bool getParameter(const String &cle) override;
  private:
  CoeurReacteur* m_coeurReacteur;
 public:
  InterpreteurCommandeSpecifique(Stream &stream, CoeurReacteur* p_coeurReacteur);
};