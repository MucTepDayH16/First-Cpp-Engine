#ifndef INPUT_H
#define INPUT_H

#include "mainheader.h"

class Input {
public:
    class KeyListener {
    public:
        virtual void onKeyDown(const SDL_Keycode&);
        virtual void onKeyUp(const SDL_Keycode&);
    };
    static bool setOnKeyListener(KeyListener*);

    class QuitListener {
    public:
        virtual void onQuit(const Uint16&);
    };
    static bool setOnQuitListener(QuitListener*);

    class MouseListener {
    public:
        virtual void onMouseDown(const Uint8&);
        virtual void onMouseUp(const Uint8&);
    };
    static bool setOnMouseListener(MouseListener*);

    static bool InitInput();

    static bool Update();

    static Uint8 isKeyPressed(const SDL_Keycode&);
    static Uint8 isMousePressed(const Uint8&);
    static SDL_Point* GetMousePos();

    static Uint64* GetTimer();
    static Sint64* GetDeltaTimer();

    static bool KillInput();
protected:
    static SDL_Event* EVENT;

    static set<KeyListener*>* ListenerMap;
    static set<MouseListener*>* MouseListenerMap;
    static QuitListener* Q;
    static set<SDL_Keycode>* KeyMap;
    static set<Uint8>* MouseButtons;
    static SDL_Point* MousePos;
    static Uint64 Timer;
    static Sint64 Delta;
};

#endif
