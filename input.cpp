#include "input.h"

SDL_Event* Input::EVENT(nullptr);
std::set<Input::KeyListener*>* Input::ListenerMap(nullptr);
std::set<Input::MouseListener*>* Input::MouseListenerMap(nullptr);
Input::QuitListener* Input::Q(nullptr);
std::set<SDL_Keycode>* Input::KeyMap(nullptr);
std::set<Uint8>* Input::MouseButtons(nullptr);
SDL_Point* Input::MousePos(nullptr);
Uint64 Input::Timer(0);
Sint64 Input::Delta(0);

bool Input::InitInput() {
  SDL_Init(SDL_INIT_EVENTS);

  EVENT             = new SDL_Event;
  ListenerMap       = new std::set<KeyListener*>;
  MouseListenerMap  = new std::set<MouseListener*>;
  KeyMap            = new std::set<SDL_Keycode>;
  MouseButtons      = new std::set<Uint8>;
  MousePos          = new SDL_Point; MousePos->x = 0; MousePos->y = 0;
  Q                 = nullptr;
  Timer             = SDL_GetTicks();
  Delta             = 0;

  while (SDL_PollEvent(EVENT)) {}

  return true;
}

bool Input::Update() {
  while(SDL_PollEvent(EVENT)) {
    switch (EVENT->type) {
      case SDL_KEYDOWN:
        if (KeyMap->count(EVENT->key.keysym.sym) == 0) {
          for (KeyListener *K : *ListenerMap) {
            K->onKeyDown(EVENT->key.keysym.sym);
          }
          KeyMap->emplace(EVENT->key.keysym.sym);
        }
        break;

      case SDL_KEYUP:
        for (KeyListener *K : *ListenerMap) {
          K->onKeyUp(EVENT->key.keysym.sym);
        }
        KeyMap->erase(EVENT->key.keysym.sym);
        break;

      case SDL_MOUSEMOTION:
        MousePos->x   = EVENT->motion.x;
        MousePos->y   = EVENT->motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (MouseButtons->count(EVENT->button.button) == 0) {
          for (MouseListener *M : *MouseListenerMap) {
            M->onMouseDown(EVENT->button.button);
          }
          MouseButtons->emplace(EVENT->button.button);
        }
        break;

      case SDL_MOUSEBUTTONUP:
        for (MouseListener *M : *MouseListenerMap) {
          M->onMouseUp(EVENT->button.button);
        }
        MouseButtons->erase(EVENT->button.button);
        break;

      case SDL_QUIT:
        Q->onQuit(CODE::_SAFE_QUIT);
        break;

    }
  }

  Delta = SDL_GetTicks() - Timer;
  Timer += Delta;
  return true;
}

Uint8 Input::isKeyPressed(const SDL_Keycode& Key) {
  return Uint8(KeyMap->count(Key));
}

Uint8 Input::isMousePressed(const Uint8& Button) {
  return Uint8(MouseButtons->count(Button));
}

SDL_Point* Input::GetMousePos() {
  return MousePos;
}

Uint64* Input::GetTimer() {
  return &Timer;
}

Sint64* Input::GetDeltaTimer() {
  return &Delta;
}

bool Input::KillInput() {
  return true;
}
