#include "execute.h"

void Execute::Exit(Uint16 code) {
  Graphic::KillGraphic();
  Input::KillInput();

  exit = code;
  isRunning = false;
}

Execute::Execute(State* start_state, Uint16 width, Uint16 height)
    : exit(0), isRunning(true), state(start_state) {
    Graphic::InitGraphic(width, height);
    Input::InitInput();

    state->Create();
}

Uint16 Execute::Run() {
    while (isRunning) try {
        if (!state->Run()) throw new Quit(CODE::_NOT_RUNNING);
    }
    catch (Quit* e) {
        Exit(e->code);
    }
    catch (State* s) {
        state = s;
    }

    clog << "end" << endl;
    return exit;
}
