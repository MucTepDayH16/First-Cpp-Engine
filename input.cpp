#include "input.h"

SDL_Event* Input::EVENT(nullptr);
std::map<SDL_Keycode, Input::KeyDownListener*>* Input::ListenerMap(nullptr);
Input::QuitListener* Input::Q(nullptr);
std::set<SDL_Keycode>* Input::KeyMap(nullptr);
SDL_Point* Input::MousePos(nullptr);

bool Input::InitInput() {
  SDL_Init(SDL_INIT_EVENTS);

  EVENT         = new SDL_Event;
  ListenerMap   = new std::map<SDL_Keycode, KeyDownListener*>;
  KeyMap        = new std::set<SDL_Keycode>;
  MousePos      = new SDL_Point; MousePos->x = 0; MousePos->y = 0;
  Q             = nullptr;

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
            KeyMap->erase(EVENT->key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            MousePos->x   = EVENT->motion.x;
            MousePos->y  = EVENT->motion.y;
            break;
        case SDL_QUIT:
            Q->onQuit(CODE::_SAFE_QUIT);
            break;
        }
    }
    return true;
}

Uint8 Input::isKeyPressed(const SDL_Keycode& Key) {
    return Uint8(KeyMap->count(Key));
}

SDL_Point* Input::GetMousePos() {
    return MousePos;
}

bool Input::KillInput() {
    return true;
}
