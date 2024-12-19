#pragma once
#include <Arduino.h>
#include "config.h"
#include "Program.h"
#include "ReactorController.h"
#include "Actions/ActionChangeState.h"
#include "Tasks/ButtonChangeState.h"
#include "Tasks/LEDSynchroniser.h"
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