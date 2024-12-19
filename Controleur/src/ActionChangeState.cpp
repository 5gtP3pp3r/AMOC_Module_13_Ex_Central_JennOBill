#include "ActionChangeState.h"

ActionChangeState::ActionChangeState(
    ReactorController* p_controller
) :
    m_controller(p_controller) { ; }

void ActionChangeState::execute() {
    if (this->m_controller->getReactorState() == "actif") {
        this->m_controller->shutReactor();
    }
    else {
        this->m_controller->activateReactor();
    }
}