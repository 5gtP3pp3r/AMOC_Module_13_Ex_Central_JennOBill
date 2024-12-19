#pragma once

#include <Arduino.h>

#include "LED.h"
#include "Action.h"
#include "ReactorController.h"

class ActionChangeState : public Action {
private:
    ReactorController* m_controller;

public:
    ActionChangeState(
        ReactorController* p_controller
        );
    void execute() override;   
};