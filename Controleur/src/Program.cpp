#include "Program.h"

Program::Program() { 
  this->m_greenLED = new LED(GREEN_PIN);
  this->m_redLED = new LED(RED_PIN);
  this->m_connection = new Connection(INTERVAL_5);
  this->m_reactorController = new ReactorController(
    this->m_connection,
    INTERVAL_2
  );
  this->m_actionChangeState = new ActionChangeState(
    this->m_reactorController
  );
  this->m_LEDSynchroniser = new LEDSynchroniser(
    this->m_greenLED,
    this->m_redLED,
    this->m_reactorController,
    INTERVAL_1
  );
  this->m_buttonChangeState = new ButtonChangeState(
    BUTTON_PIN,
    INTERVAL_40,
    this->m_actionChangeState
  );
  this->m_connection->connectToNetwork();
  this->m_reactorController->getURL();
}

void Program::loop() {
  this->m_reactorController->tick();
  this->m_buttonChangeState->tick();
  this->m_LEDSynchroniser->tick(); 
  this->m_connection->tick();
}
// reste à implémenter Terminal.h/cpp