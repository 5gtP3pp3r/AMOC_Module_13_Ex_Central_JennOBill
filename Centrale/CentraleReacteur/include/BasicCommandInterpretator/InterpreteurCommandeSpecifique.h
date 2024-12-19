#pragma once

#include "InterpreteurCommande.h"

class InterpreteurCommandeSpecifique : public InterpreteurCommande {
 protected:
  virtual bool interpreter(const String &commande,
                         const String &parametres) override;
  virtual bool getParametre(const String &cle) override;

 public:
  InterpreteurCommandeSpecifique(Stream &stream);
};