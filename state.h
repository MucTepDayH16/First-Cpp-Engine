#ifndef STATE_H
#define STATE_H

#include "entity.h"

class State {
protected:
    static bool ChangeState(State*);
    set<Entity*>* Entities;
public:
    State();
    virtual bool Create();

    virtual bool Run();

    class Start;
};

class Quit : public State {
public:
    Uint16 code;
    Quit(Uint16);
    bool Run() override;
};

class Start : public State,
        Input::KeyListener,
        Input::MouseListener,
        Input::QuitListener {
protected:
    MaterialPoint *New;
    SDL_Point *Mouse0;
    SDL_Point *Mouse;
    set<MaterialPoint*> *Field;
    double field(const double&, const double&, const double&, const double&);
public:
    Start();

    bool Create() override;
    bool Run() override;

    void onKeyDown(const SDL_Keycode&) override;
    void onKeyUp(const SDL_Keycode&) override;
    void onQuit(const Uint16& code) override;
    void onMouseDown(const Uint8&) override;
    void onMouseUp(const Uint8&) override;
};

#endif