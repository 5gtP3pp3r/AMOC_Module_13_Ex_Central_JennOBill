#pragma once
#include <Arduino.h>
#include "DEL.h"
#include "Action.h"
#include "ControleurReacteur.h"

class ActionChangerEtat : public Action {
private:
    ControleurReacteur* m_controleur;

public:
    ActionChangerEtat(
        ControleurReacteur* p_controleur
        );
    void executer() override;   
};