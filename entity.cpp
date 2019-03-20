#include "entity.h"

Entity::Entity(const Uint16& w, const Uint16& h, const Uint16& x, const Uint16& y)
: Alive(true), Pos(x, y), Size(new SDL_Rect) {
    Size->w = w; Size->h = h;
    Size->x = int(Pos.x) - Size->w/2;
    Size->y = int(Pos.y) - Size->h/2;
}

bool Entity::Living() {
    Size->x = int(Pos.x) - Size->w/2;
    Size->y = int(Pos.y) - Size->h/2;

    return Alive;
}

void Entity::Kill() {
    Alive = false;
}

SDL_Texture* MaterialPoint::MainTexture(nullptr);

MaterialPoint::MaterialPoint(const Uint16& X, const Uint16& Y, const Uint16& M, set<MaterialPoint*>* field) 
: Entity(Const::Diameter, Const::Diameter, X, Y), Mass(M), Vel(0, 0), Acc(0, 0), Field(field) {
	if (MainTexture == nullptr)
		MainTexture = Graphic::LoadTexture("res/M.png");
	Acc.x = 0.; Acc.y = 1.;
}

bool MaterialPoint::Living() {
	static Sint64* Delta = Input::GetDeltaTimer();

	if (Pos.x <= 0 || Pos.x >= Graphic::WIDTH) {
		while (Pos.x <= 0)
			Pos.x += .1;
		while (Pos.x >= Graphic::WIDTH)
			Pos.x -= .1;
		Vel.x *= -.95;
	}

	if (Pos.y <= 0 || Pos.y >= Graphic::HEIGHT) {
		while (Pos.y <= 0)
			Pos.y += .1;
		while (Pos.y >= Graphic::HEIGHT)
			Pos.y -= .1;
		Vel.y *= -.95;
	}

	for (MaterialPoint *M : *Field) {
		if (this == M)
			continue;

		double D = sqrt(.01 + (Pos.x - M->Pos.x) * (Pos.x - M->Pos.x) + (Pos.y - M->Pos.y) * (Pos.y - M->Pos.y));
		Point N((Pos.x - M->Pos.x) / D, (Pos.y - M->Pos.y) / D);
		if (D <= Const::Diameter) {
			while (Const::Diameter * Const::Diameter >= .01 + (Pos.x - M->Pos.x) * (Pos.x - M->Pos.x) + (Pos.y - M->Pos.y) * (Pos.y - M->Pos.y)) {
				Pos.x += 		.05 * N.x;
				Pos.y += 		.05 * N.y;
				M->Pos.x -= 	.05 * N.x;
				M->Pos.y -= 	.05 * N.y;
			}

			double Pr = ((Vel.x - M->Vel.x) * N.x + (Vel.y - M->Vel.y) * N.y) * 2. / (M->Mass + Mass);

			Vel.x -= 		M->Mass * Pr * N.x;
			Vel.y -= 		M->Mass * Pr * N.y;
			M->Vel.x += 	Mass 	* Pr * N.x;
			M->Vel.y +=		Mass 	* Pr * N.y;
		}
	}

	Pos.x += Vel.x * double(*Delta) / 1000.;
	Pos.y += Vel.y * double(*Delta) / 1000.;

	Vel.x += Acc.x * double(*Delta) / 1000.;
	Vel.y += Acc.y * double(*Delta) / 1000.;

	Graphic::DrawTexture(Size, MainTexture);
	return Entity::Living();
}

void MaterialPoint::setVelocity(SDL_Point *vel) {
	Vel.x = vel->x;
	Vel.y = vel->y;
}