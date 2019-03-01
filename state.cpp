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

Start::Start()
    : State(), Mouse(new SDL_Point) {}

bool Start::Create() {
    State::Create();
    Mouse = Input::GetMousePos();

    Input::setOnKeyDownListener(SDLK_SPACE, this);
    Input::setOnKeyDownListener(SDLK_n, this);
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
        clog << Entities->size() << endl;
        break;
    }
}

void Start::onQuit(const Uint16& code) {
    throw new Quit(code);
}
