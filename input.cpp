#include "input.h"

SDL_Event* Input::EVENT(nullptr);
std::map<SDL_Keycode, Input::KeyListener*>* Input::ListenerMap(nullptr);
Input::QuitListener* Input::Q(nullptr);
std::set<SDL_Keycode>* Input::KeyMap(nullptr);
SDL_Point* Input::MousePos(nullptr);
Uint64 Input::Timer(0);
Uint64 Input::Delta(0);

bool Input::InitInput() {
  SDL_Init(SDL_INIT_EVENTS);

  EVENT         = new SDL_Event;
  ListenerMap   = new std::map<SDL_Keycode, KeyListener*>;
  KeyMap        = new std::set<SDL_Keycode>;
  MousePos      = new SDL_Point; MousePos->x = 0; MousePos->y = 0;
  Q             = nullptr;
  Timer         = SDL_GetTicks();
  Delta         = 0;

  while (SDL_PollEvent(EVENT)) {}

  return true;
}

bool Input::Update() {
  while(SDL_PollEvent(EVENT)) {
    switch (EVENT->type) {
      case SDL_KEYDOWN:
        if (KeyMap->count(EVENT->key.keysym.sym) == 0)
        {
          if (ListenerMap->count(EVENT->key.keysym.sym) > 0)
            (*ListenerMap->find(EVENT->key.keysym.sym)).second->onKeyDown(EVENT->key.keysym.sym);
          KeyMap->emplace(EVENT->key.keysym.sym);
        }
        break;

      case SDL_KEYUP:
        if (ListenerMap->count(EVENT->key.keysym.sym) > 0)
          (*ListenerMap->find(EVENT->key.keysym.sym)).second->onKeyUp(EVENT->key.keysym.sym);
        KeyMap->erase(EVENT->key.keysym.sym);
        break;

      case SDL_MOUSEMOTION:
        MousePos->x   = EVENT->motion.x;
        MousePos->y  = EVENT->motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        
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

SDL_Point* Input::GetMousePos() {
  return MousePos;
}

Uint64* Input::GetTimer() {
  return &Timer;
}

Uint64* Input::GetDeltaTimer() {
  return &Delta;
}

bool Input::KillInput() {
  return true;
}
