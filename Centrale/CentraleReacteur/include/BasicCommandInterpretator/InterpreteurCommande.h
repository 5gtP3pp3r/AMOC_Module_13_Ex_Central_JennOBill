#pragma once

#include <Arduino.h>
#include <Stream.h>

class InterpreteurCommande {
 private:
  Stream &m_stream;
  String m_derniereEntreeSerie;

 protected:
  virtual bool interpreter(const String &commande, const String &parametres);
  virtual bool getParametre(const String &cle);
  virtual bool setParametre(const String &cle, const String &valeur);

 public:
  InterpreteurCommande(Stream &m_fileDeCommande);
  void tick();
  bool executerCommande(const String &commande);
};