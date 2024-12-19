#include <Arduino.h>
#include "Program.h"
#include "BasicCommandInterpretator/Logger.h"

Program* program;

void setup() {
  Serial.begin(115200);
  Logger.begin(&Serial);
  program = new Program();
  program->connexionReseau();
}

void loop() {
  program->loop();
}
