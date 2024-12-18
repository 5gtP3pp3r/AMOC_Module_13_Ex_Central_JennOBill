#include "BasicCommandInterpretator\InterpreteurCommande.h"
#include <Arduino.h>
#include <Stream.h>
#include "Constantes.h"
#include "BasicCommandInterpretator\Logger.h"

#include "BasicCommandInterpretator\StringUtil.h"

String activer = "activer";
String desactiver = "desactiver";
String statut = "statut";

InterpreteurCommande::InterpreteurCommande(Stream &p_stream)
    : m_stream(p_stream), m_derniereEntreeSerie("") {
  ;
}

void InterpreteurCommande::tick() {
  while (this->m_stream.available()) {
    char c = this->m_stream.read();
    if (c == '\n') {
      this->executerCommande(m_derniereEntreeSerie);
      this->m_derniereEntreeSerie = "";
    } else {
      this->m_derniereEntreeSerie += c;
    }
  }
}

bool InterpreteurCommande::executerCommande(const String &p_commande) {
  String cmd = p_commande;

  String parametres = "";
  int index = cmd.indexOf(' ');
  if (index != -1) {
    parametres = cmd.substring(index + 1);
    cmd = cmd.substring(0, index);
  }
  cmd.trim();
  parametres.trim();

  Logger.println(String(F("> ")) + cmd + " " + parametres);

  return this->interpreter(cmd, parametres);
}

bool InterpreteurCommande::interpreter(const String &p_commande,
                                        const String &p_parametres) {
  bool erreur = false;

  if (p_commande == "coeur-reacteur") {
     if(p_parametres == activer){
        
     }else if(p_parametres == "desactiver"){

     }else if(p_parametres == "statut"){

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

bool InterpreteurCommande::getParametre(const String &cle) {
  bool erreur = false;

  if (cle == "debug") {
    Logger.println(String(F("debug: ")) + Logger.getLoggerLevel());
  } else {
    Logger.errorln(F("get : cle invalide"));
    erreur = true;
  }

  return !erreur;
}