#include "state.h"

Start::Start() 
: State(), Mouse(nullptr), Field(new set<MaterialPoint*>) {}

double Start::field(const double& t, const double& x, const double& y, const double& z) {
    double F = 0;
    return F;
}

bool Start::Create() {
    State::Create();
    Mouse = Input::GetMousePos();

    Input::setOnKeyListener(this);
    Input::setOnMouseListener(this);
    Input::setOnQuitListener(this);

    return true;
}

bool Start::Run() {
    if (Input::isKeyPressed(SDLK_RIGHT))
        (*Input::GetDeltaTimer()) *= 20;

    return 
        State::Run() &&
        Input::Update() &&
        Graphic::Update(0xff);
}

void Start::onKeyDown(const SDL_Keycode& Key) {
    switch (Key) {
    case SDLK_SPACE:
        Entity* NEW = new MaterialPoint(Mouse->x, Mouse->y, 1000, Field);
        Entities->emplace(NEW);
        Field->emplace((MaterialPoint*)NEW);
        break;
    }
}

void Start::onKeyUp(const SDL_Keycode& Key) {
    
}

void Start::onQuit(const Uint16& code) {
    ChangeState(new Quit(code));
}

void Start::onMouseDown(const Uint8& Button) {
    switch (Button) {
    default:
        Entity* NEW = new MaterialPoint(Mouse->x, Mouse->y, 100, Field);
        Entities->emplace(NEW);
        Field->emplace((MaterialPoint*)NEW);
        break;
    }
}

void Start::onMouseUp(const Uint8& Button) {
    
}