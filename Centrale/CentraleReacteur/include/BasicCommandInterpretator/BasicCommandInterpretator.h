#pragma once

#include <Arduino.h>
#include <Stream.h>

// Source: PIFOU : https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo

class BasicCommandInterpretator {
 private:
  Stream &m_stream;
  String m_lastSerialInput;

 protected:
  virtual bool interpret(const String &command, const String &parameters);
  virtual bool getParameter(const String &key);
  virtual bool setParameter(const String &key, const String &value);

 public:
  BasicCommandInterpretator(Stream &stream);
  void tick();
  bool executeCommand(const String &command);
};