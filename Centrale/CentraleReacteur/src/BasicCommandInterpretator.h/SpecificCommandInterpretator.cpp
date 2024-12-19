#include "BasicCommandInterpretator/SpecificCommandInterpretator.h"

#include "BasicCommandInterpretator/Logger.h"

String activate = "activer";
String deactivate = "desactiver";
String state = "statut";

SpecificCommandInterpretator::SpecificCommandInterpretator(Stream &stream, ReactorHeart* p_reactorHeart)
    : BasicCommandInterpretator(stream), m_reactorHeart(p_reactorHeart) {
  ;
}

bool SpecificCommandInterpretator::interpret(const String &p_command,
                                           const String &p_parameters) {
  bool error = false;

  if (p_command == "coeur-reacteur") {
     if(p_parameters == activate){
        this->m_reactorHeart->activate();
     }else if(p_parameters == "desactiver"){
      this->m_reactorHeart->deactivate();
     }else if(p_parameters == "statut"){
      String statut = this->m_reactorHeart->getState();
      Logger.println("Le statut du réacteur est: " + statut);
     }
    }
  else if (p_command == "help") {
    Logger.println(F("Commandes disponibles:"));
    Logger.println(F("  coeur-reacteur statut"));
    Logger.println(F("  coeur-reacteur activer"));
    Logger.println(F("  coeur-reacteur desactiver"));
    Logger.println(F("  help"));
    BasicCommandInterpretator::interpret(p_command, p_parameters);
  } else {
    BasicCommandInterpretator::interpret(p_command, p_parameters);

    Logger.errorln(String(F("Commande inconnue: ")) + p_command);
    error = true;
  }

  return !error;
}

bool SpecificCommandInterpretator::getParameter(const String &p_key) {
  return BasicCommandInterpretator::getParameter(p_key);
}

