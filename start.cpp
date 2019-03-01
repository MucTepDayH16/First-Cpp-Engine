#include "state.h"

Start::Start() : State(), Mouse(new SDL_Point) {}

bool Start::Create() {
    State::Create();
    Mouse = Input::GetMousePos();

    Input::setOnKeyListener(SDLK_SPACE, this);
    Input::setOnKeyListener(SDLK_n, this);
    Input::setOnQuitListener(this);

    return true;
}

bool Start::Run() {
    return 
        State::Run() &&
        Input::Update() &&
        Graphic::Update(Input::isKeyPressed(SDLK_SPACE) ? 0x7f : 0xff);
}

void Start::onKeyDown(const SDL_Keycode& Key) {
    switch (Key) {
    case SDLK_SPACE:
        Entities->emplace(new Entity("res/M.png", 2, 2, Mouse->x, Mouse->y));
        break;

    case SDLK_n:
        break;

    }
}

void Start::onKeyUp(const SDL_Keycode&) {
    
}

void Start::onQuit(const Uint16& code) {
    ChangeState(new Quit(code));
}