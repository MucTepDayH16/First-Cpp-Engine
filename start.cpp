#include "state.h"

Start::Start() 
: State(), New(nullptr), Mouse0(new SDL_Point), Mouse(nullptr), Field(new set<MaterialPoint*>) {}

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

    if (Input::isMousePressed(SDL_BUTTON_LEFT))
        Graphic::DrawLine(Mouse, Mouse0);

    return 
        State::Run() &&
        Input::Update() &&
        Graphic::Update(0xff);
}

void Start::onKeyDown(const SDL_Keycode& Key) {
    switch (Key) {
    case SDLK_SPACE: {
        MaterialPoint* NEW = new MaterialPoint(Mouse->x, Mouse->y, Const::HeavyMass, Field);
        Entities->emplace(NEW);
        Field->emplace(NEW);
        break; }
    case SDLK_n: {
        cerr << Entities->size() << endl;
        break; }
    }
}

void Start::onKeyUp(const SDL_Keycode& Key) {
    
}

void Start::onQuit(const Uint16& code) {
    ChangeState(new Quit(code));
}

void Start::onMouseDown(const Uint8& Button) {
    switch (Button) {
    case SDL_BUTTON_LEFT:
        New = new MaterialPoint(Mouse->x, Mouse->y, Const::LightMass, Field);
        Mouse0->x = Mouse->x;
        Mouse0->y = Mouse->y;
        break;
    }
}

void Start::onMouseUp(const Uint8& Button) {
    switch (Button) {
    case SDL_BUTTON_LEFT:
        Mouse0->x = -(2) * (Mouse0->x - Mouse->x);
        Mouse0->y = -(2) * (Mouse0->y - Mouse->y);
        New->setVelocity(Mouse0);
        Entities->emplace(New);
        Field->emplace(New);
        break;
    }
}