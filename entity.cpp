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

MaterialPoint::MaterialPoint(const Uint16& X, const Uint16& Y, const Uint16& M, set<MaterialPoint*>* field) 
: Entity("res/M.png", DIAMETER, DIAMETER, X, Y), Mass(M), Vel(0, 0), Acc(0, 0), Field(field) {}

bool MaterialPoint::Living() {
	static Uint64* Delta = Input::GetDeltaTimer();

	Acc.x = 0.; Acc.y = 0.;
	for (MaterialPoint *M : *Field) {
		if (this == M)
			continue;

		double D = sqrt(.1 + (Pos.x - M->Pos.x) * (Pos.x - M->Pos.x) + (Pos.y - M->Pos.y) * (Pos.y - M->Pos.y));
		if (D < DIAMETER) {
			Point N((Pos.x - M->Pos.x)/D, (Pos.y - M->Pos.y)/D), Vel1(Vel), Vel2(M->Vel);

			Vel.x += 	((Vel2.x - Vel1.x) * N.x + (Vel2.y - Vel1.y) * N.y) * N.x;
			Vel.y += 	((Vel2.x - Vel1.x) * N.x + (Vel2.y - Vel1.y) * N.y) * N.y;
			M->Vel.x += ((Vel1.x - Vel2.x) * N.x + (Vel1.y - Vel2.y) * N.y) * N.x;
			M->Vel.y += ((Vel1.x - Vel2.x) * N.x + (Vel1.y - Vel2.y) * N.y) * N.y;
		}

		double K = (GRAVITY) * M->Mass / (D * D * D);

		Acc.x += K * (Pos.x - M->Pos.x);
		Acc.y += K * (Pos.y - M->Pos.y);
	}

	Pos.x += Vel.x * double(*Delta) / 1000.;
	Pos.y += Vel.y * double(*Delta) / 1000.;

	Vel.x += Acc.x * double(*Delta) / 1000.;
	Vel.y += Acc.y * double(*Delta) / 1000.;

	return Entity::Living();
}