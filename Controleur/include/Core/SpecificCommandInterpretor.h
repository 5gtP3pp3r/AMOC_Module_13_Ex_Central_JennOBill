#pragma once

#include "BasicCommandInterpretor.h"

#include "../ReactorController.h"

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