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
        Input::QuitListener {
protected:
    SDL_Point* Mouse;
public:
    Start();

    bool Create() override;
    bool Run() override;

    void onKeyDown(const SDL_Keycode& Key) override;
    void onKeyUp(const SDL_Keycode&) override;
    void onQuit(const Uint16& code) override;
};

#endif