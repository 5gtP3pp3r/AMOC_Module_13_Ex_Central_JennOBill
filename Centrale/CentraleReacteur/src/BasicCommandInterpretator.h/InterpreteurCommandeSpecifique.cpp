#include "BasicCommandInterpretator/InterpreteurCommandeSpecifique.h"

#include "BasicCommandInterpretator/Logger.h"

InterpreteurCommandeSpecifique::InterpreteurCommandeSpecifique(Stream &stream)
    : InterpreteurCommande(stream) {
  ;
}

bool InterpreteurCommandeSpecifique::interpreter(const String &p_commande,
                                           const String &p_parametres) {
  bool erreur = false;

  if (p_commande == "specific") {
    Logger.println(F("specific Hello, world!"));
  } else if (p_commande == "help") {
    Logger.println(F(""));
    Logger.println(F("  specific"));
    Logger.println(F(""));
    InterpreteurCommande::interpreter(p_commande, p_parametres);
  } else {
    erreur = !InterpreteurCommande::interpreter(p_commande, p_parametres);
  }

  return !erreur;
}

bool InterpreteurCommandeSpecifique::getParametre(const String &p_cle) {
  return InterpreteurCommande::getParametre(p_cle);
}

