#pragma once

#include <Arduino.h>

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo
class StringUtil {
public:
  static String padLeft(const String &value, char padChar, unsigned int length);
};
