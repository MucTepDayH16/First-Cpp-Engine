#include "state.h"

State::State()
    : Entities(new set<Entity*>) {}

bool State::Create() {
    return true;
}

bool State::Run() {
    for (Entity* E : *Entities) {
        E->Living();
    }

    return true;
}

bool State::ChangeState(State* state) {
    throw state;
}

Quit::Quit(Uint16 code)
    : code(code) {}

bool Quit::Run() {
    return false;
}
