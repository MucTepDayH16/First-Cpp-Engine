#include "input.h"

void Input::KeyListener::onKeyDown(const SDL_Keycode&) {}

bool Input::setOnKeyListener(KeyListener* L) {
	ListenerMap->emplace(L);
	return true;
}

void Input::KeyListener::onKeyUp(const SDL_Keycode&) {}

void Input::QuitListener::onQuit(const Uint16&) {}

bool Input::setOnQuitListener(QuitListener* L) {
    Q = L;
    return true;
}

void Input::MouseListener::onMouseDown(const Uint8&) {}

void Input::MouseListener::onMouseUp(const Uint8&) {}

bool Input::setOnMouseListener(MouseListener* L) {
	MouseListenerMap->emplace(L);
	return true;
}