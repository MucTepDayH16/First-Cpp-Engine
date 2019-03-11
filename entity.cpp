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
: Entity(20, 20, X, Y), Mass(M), Vel(0, 0), Acc(0, 0), Field(field) {
	if (MainTexture == nullptr)
		MainTexture = Graphic::LoadTexture("res/M.png");
}

bool MaterialPoint::Living() {
	static Sint64* Delta = Input::GetDeltaTimer();

	Acc.x = 0.; Acc.y = 0.;
	for (MaterialPoint *M : *Field) {
		if (this == M)
			continue;

		double D = sqrt(.01 + (Pos.x - M->Pos.x) * (Pos.x - M->Pos.x) + (Pos.y - M->Pos.y) * (Pos.y - M->Pos.y));
		Point N((Pos.x - M->Pos.x) / D, (Pos.y - M->Pos.y) / D);
		if (D <= 20) {
			while (400 >= .01 + (Pos.x - M->Pos.x) * (Pos.x - M->Pos.x) + (Pos.y - M->Pos.y) * (Pos.y - M->Pos.y)) {
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

		double K = (-100) * M->Mass / (D * D);

		Acc.x += K * N.x;
		Acc.y += K * N.y;
	}

	Pos.x += Vel.x * double(*Delta) / 1000.;
	Pos.y += Vel.y * double(*Delta) / 1000.;

	Vel.x += Acc.x * double(*Delta) / 1000.;
	Vel.y += Acc.y * double(*Delta) / 1000.;

	Graphic::DrawTexture(Size, MainTexture);
	return Entity::Living();
}