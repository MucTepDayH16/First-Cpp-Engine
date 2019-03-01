#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "mainheader.h"

class Graphic {
protected:
    static Uint16 WIDTH, HEIGHT;
    static SDL_Window* Win;
    static SDL_Renderer* Rend;
public:
    struct Color {
        Uint8 r, g, b, a;
        Color(
                const Uint8& a,
                const Uint8& r = 0x00,
                const Uint8& g = 0x00,
                const Uint8& b = 0x00
                )
            : r(r), g(g), b(b), a(a) {}
    };

    static bool InitGraphic(Uint16, Uint16);

    static bool SetColor(Color*);
    static SDL_Texture* LoadTexture(const char*);
    static bool DrawTexture(SDL_Rect*, SDL_Texture*);
    static bool DrawRect(SDL_Rect*);

    static bool Update();
    static bool Update(const Uint8&);
    static bool Update(const Uint8&, const Uint8&, const Uint8&);

    static bool KillGraphic();
};

#endif
