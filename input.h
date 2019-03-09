#ifndef INPUT_H
#define INPUT_H

#include "mainheader.h"

class Input {
public:
    class KeyListener
    {
    public:
        virtual void onKeyDown(const SDL_Keycode&);
        virtual void onKeyUp(const SDL_Keycode&);
    };
    static bool setOnKeyListener(SDL_Keycode, KeyListener*);

    class QuitListener
    {
    public:
        virtual void onQuit(const Uint16&);
    };
    static bool setOnQuitListener(QuitListener*);

    static bool InitInput();

    static bool Update();

    static Uint8 isKeyPressed(const SDL_Keycode&);
    static SDL_Point* GetMousePos();

    static Uint64* GetTimer();
    static Uint64* GetDeltaTimer();

    static bool KillInput();
protected:
    static SDL_Event* EVENT;

    static map<SDL_Keycode, KeyListener*>* ListenerMap;
    static QuitListener* Q;
    static set<SDL_Keycode>* KeyMap;
    static SDL_Point* MousePos;
    static Uint64 Timer;
    static Uint64 Delta;
};

#endif
