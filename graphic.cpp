#include "graphic.h"

Uint16 Graphic::WIDTH(0);
Uint16 Graphic::HEIGHT(0);
SDL_Window* Graphic::Win(nullptr);
SDL_Renderer* Graphic::Rend(nullptr);

bool Graphic::InitGraphic(Uint16 width, Uint16 height) {
    WIDTH = width; HEIGHT = height;
    SDL_Init(SDL_INIT_VIDEO);

    Win = SDL_CreateWindow(
                "Simulator",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                WIDTH,
                HEIGHT,
                SDL_WINDOW_SHOWN
                );

    Rend = SDL_CreateRenderer(
                Win,
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE
                );

    return Rend != nullptr;
}

bool Graphic::SetColor(Color* C) {
    return SDL_SetRenderDrawColor(Rend, C->r, C->g, C->b, C->a) == 0;
}

SDL_Texture* Graphic::LoadTexture(const char* path) {
    return SDL_CreateTextureFromSurface(Rend, IMG_LoadPNG_RW(SDL_RWFromFile(path, "rb")));
}

bool Graphic::DrawTexture(SDL_Rect* pos, SDL_Texture* text) {
    return SDL_RenderCopy(Rend, text, nullptr, pos) == 0;
}

bool Graphic::DrawRect(SDL_Rect* pos) {
    return SDL_RenderFillRect(Rend, pos) == 0;
}

bool Graphic::Update() {
    SDL_RenderPresent(Rend);

    return SDL_RenderClear(Rend) == 0;
}

bool Graphic::Update(const Uint8& g) {
    SDL_RenderPresent(Rend);

    SDL_SetRenderDrawColor(Rend, g, g, g, 0x00);
    return SDL_RenderClear(Rend) == 0;
}

bool Graphic::Update(const Uint8& r, const Uint8& g, const Uint8& b) {
    SDL_RenderPresent(Rend);

    SDL_SetRenderDrawColor(Rend, r, g, b, 0x00);
    return SDL_RenderClear(Rend) == 0;
}

bool Graphic::KillGraphic() {
    SDL_DestroyRenderer(Rend);
    SDL_DestroyWindow(Win);
    SDL_VideoQuit();
    SDL_Quit();

    return true;
}
