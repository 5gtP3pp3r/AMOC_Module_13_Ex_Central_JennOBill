#include "BasicCommandInterpretator/InterpreteurCommandeSpecifique.h"

#include "BasicCommandInterpretator/Logger.h"

String activer = "activer";
String desactiver = "desactiver";
String statut = "statut";

InterpreteurCommandeSpecifique::InterpreteurCommandeSpecifique(Stream &stream, CoeurReacteur* p_coeurReacteur)
    : BasicCommandInterpretator(stream), m_coeurReacteur(p_coeurReacteur) {
  ;
}

bool InterpreteurCommandeSpecifique::interpret(const String &p_commande,
                                           const String &p_parametres) {
  bool erreur = false;

  if (p_commande == "coeur-reacteur") {
     if(p_parametres == activer){
        this->m_coeurReacteur->activer();
     }else if(p_parametres == "desactiver"){
      this->m_coeurReacteur->desactiver();
     }else if(p_parametres == "statut"){
      bool estActif = this->m_coeurReacteur->getStatut();
      Logger.println("Le statut du réacteur est: " + estActif? "actif" : "inactif");
     }
    }
  else if (p_commande == "help") {
    Logger.println(F("Commandes disponibles:"));
    Logger.println(F("  coeur-reacteur statut"));
    Logger.println(F("  coeur-reacteur activer"));
    Logger.println(F("  coeur-reacteur desactiver"));
    Logger.println(F("  help"));
  } else {
    Logger.errorln(String(F("Commande inconnue: ")) + p_commande);
    erreur = true;
  }

  return !erreur;
}

bool InterpreteurCommandeSpecifique::getParameter(const String &p_cle) {
  return BasicCommandInterpretator::getParameter(p_cle);
}

