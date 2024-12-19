#pragma once
#include <Arduino.h>
#include "config.h"
#include "Program.h"
#include "ReactorController.h"
#include "ActionChangeState.h"
#include "ButtonChangeState.h"
#include "LEDSynchroniser.h"
#include "Connection.h"
#include "LED.h"
class Program {
private:
  LED* m_greenLED;
  LED* m_redLED;
  
  ActionChangeState* m_actionChangeState;
  ButtonChangeState* m_buttonChangeState;
  ReactorController* m_reactorController;
  LEDSynchroniser* m_LEDSynchroniser;
  
public:
  Connection* m_connection;
  Program();
  void loop(); 
};  