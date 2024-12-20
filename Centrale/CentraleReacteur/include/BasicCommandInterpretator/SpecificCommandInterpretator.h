#pragma once
#include "BasicCommandInterpretator.h"
#include "ReactorHeart.h"

class SpecificCommandInterpretator : public BasicCommandInterpretator
{
protected:
  virtual bool interpret(const String &command,
                         const String &parameters) override;
  virtual bool getParameter(const String &key) override;

private:
  ReactorHeart *m_reactorHeart;

public:
  SpecificCommandInterpretator(Stream &stream, ReactorHeart *p_coeurReacteur);
};