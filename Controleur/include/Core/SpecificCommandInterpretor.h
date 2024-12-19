#pragma once

#include "BasicCommandInterpretor.h"

#include "../ReactorController.h"

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
class SpecificCommandInterpretor : public BasicCommandInterpretor {
protected:
  virtual bool interpret(const String &command,
                         const String &parameters) override;
  virtual bool getParameter(const String &key) override;
  virtual bool setParameter(const String &key, const String &value) override;

private:
  ReactorController* m_controller;

public:
  SpecificCommandInterpretor(
    Stream &stream,
    ReactorController* p_controller
    );
};