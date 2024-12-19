#include "Core/StringUtil.h"

// SOURCE: \O/ PIFOU!! https://github.com/PiFou86/420-W48-SF-Utilitaires-Demo

String StringUtil::padLeft(const String &value, char padChar, unsigned int length) {
  String result = value;
  while (result.length() < length) {
    result = padChar + result;
  }
  return result;
}
