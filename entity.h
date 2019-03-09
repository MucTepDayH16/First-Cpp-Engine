#ifndef ENTITY_H
#define ENTITY_H

#include "graphic.h"
#include "input.h"

struct Point {
    double x, y;
    Point(const double& x, const double& y) : x(x), y(y) {}
};

class Entity {
protected:
    bool Alive;
    Point Pos;
    SDL_Rect* Size;

    SDL_Texture* MainTexture;
public:
    Entity(const char*, const Uint16& = 1, const Uint16& = 1, const Uint16& = 0, const Uint16& = 0);

    virtual bool Living();

    void Kill();
};

class MaterialPoint : public Entity {
protected:
	Uint16 Mass;
	Point Vel, Acc;
	set<MaterialPoint*> *Field;
public:
	MaterialPoint(const Uint16&, const Uint16&, const Uint16&, set<MaterialPoint*>*);

	bool Living() override;
};

#endif
