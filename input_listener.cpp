#include "input.h"

void Input::KeyDownListener::onKeyDown(const SDL_Keycode&) {}

bool Input::setOnKeyDownListener(SDL_Keycode K, KeyDownListener* L) {
    if (ListenerMap->count(K) == 0)
        ListenerMap->emplace(std::pair<SDL_Keycode, KeyDownListener*>(K, L));
    else
        (*ListenerMap->find(K)).second = L;
}

void Input::QuitListener::onQuit(const Uint16&) {}

bool Input::setOnQuitListener(QuitListener* L) {
    Q = L;
}
