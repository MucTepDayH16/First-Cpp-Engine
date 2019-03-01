#include "input.h"

void Input::KeyListener::onKeyDown(const SDL_Keycode&) {}

bool Input::setOnKeyListener(SDL_Keycode K, KeyListener* L) {
    if (ListenerMap->count(K) == 0)
        ListenerMap->emplace(pair<SDL_Keycode, KeyListener*>(K, L));
    else
        (*ListenerMap->find(K)).second = L;
}

void Input::KeyListener::onKeyUp(const SDL_Keycode&) {}

void Input::QuitListener::onQuit(const Uint16&) {}

bool Input::setOnQuitListener(QuitListener* L) {
    Q = L;
}
