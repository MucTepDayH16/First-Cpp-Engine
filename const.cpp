#include "const.h"

lua_State *Const::State(nullptr);

double Const::Gravity(100);
double Const::Diameter(20);
double Const::HeavyMass(1000);
double Const::LightMass(10);

bool Const::InitConst() {
	State = luaL_newstate();
	luaL_openlibs(State);
	if (luaL_loadfile(State, "data.lua") != LUA_OK)
		return false;
	if (lua_pcall(State, 0, LUA_MULTRET, 0) != LUA_OK)
		return false;

	return true;
}

bool Const::KillConst() {
	lua_close(State);

	return true;
}