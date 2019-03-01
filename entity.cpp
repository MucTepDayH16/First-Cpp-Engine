#include "entity.h"

Entity::Entity(const char* path, const Uint16& w, const Uint16& h, const Uint16& x, const Uint16& y)
    : Alive(true), Pos(x, y), Size(new SDL_Rect), MainTexture(Graphic::LoadTexture(path)) {
    Size->w = w; Size->h = h;
    Size->x = int(Pos.x) - Size->w/2;
    Size->y = int(Pos.y) - Size->h/2;
}

bool Entity::Living() {
    Size->x = int(Pos.x) - Size->w/2;
    Size->y = int(Pos.y) - Size->h/2;

    Graphic::DrawTexture(Size, MainTexture);

    return Alive;
}

void Entity::Kill() {
    Alive = false;
}
