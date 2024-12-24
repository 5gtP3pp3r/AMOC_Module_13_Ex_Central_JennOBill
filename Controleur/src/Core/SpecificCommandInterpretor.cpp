#include "Core/SpecificCommandInterpretor.h"

#include "Log/Logger.h"

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
// Modifié pour adapter à mon projet \o/

SpecificCommandInterpretor::SpecificCommandInterpretor(
  Stream &stream,
  ReactorController* p_controller
  )
    : BasicCommandInterpretor(stream),
      m_controller(p_controller) {
  ;
}

bool SpecificCommandInterpretor::interpret(const String &command,
                                           const String &parameters) {
  bool error = false;

  if (command == "coeur-reacteur") {
    if (parameters == "statut") {
      String reactorState = m_controller->getReactorState();     
      Logger.print(F("Statut réacteur: "));
      Logger.println("\"" + reactorState + "\"");
    } else if (parameters == "activer") {
      m_controller->activateReactor();
      Logger.println(F("Réacteur activé."));
    } else if (parameters == "desactiver") {
      m_controller->shutReactor();
      Logger.println(F("Réacteur désactivé."));
    }     
  } else if (command == "help") {
    Logger.println(F("coeur-reacteur statut"));
    Logger.println(F("coeur-reacteur activer"));
    Logger.println(F("coeur-reacteur desactiver"));
    BasicCommandInterpretor::interpret(command, parameters);
  } else {
    error = !BasicCommandInterpretor::interpret(command, parameters);
  }

  return !error;
}

bool SpecificCommandInterpretor::getParameter(const String &key) {
  return BasicCommandInterpretor::getParameter(key);
}

bool SpecificCommandInterpretor::setParameter(const String &key,
                                              const String &value) {
  return BasicCommandInterpretor::setParameter(key, value);
}
