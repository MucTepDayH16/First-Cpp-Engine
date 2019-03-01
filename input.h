#ifndef INPUT_H
#define INPUT_H

#include "mainheader.h"

class Input {
public:
    class KeyDownListener
    {
    public:
        virtual void onKeyDown(const SDL_Keycode&);
    };
    static bool setOnKeyDownListener(SDL_Keycode, KeyDownListener*);

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

    static bool KillInput();
protected:
    static SDL_Event* EVENT;

    static std::map<SDL_Keycode, KeyDownListener*>* ListenerMap;
    static QuitListener* Q;
    static std::set<SDL_Keycode>* KeyMap;
    static SDL_Point* MousePos;
};

#endif
