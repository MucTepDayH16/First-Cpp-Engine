#include <lua5.3/lua.hpp>

class Const {
protected:
	static lua_State *State;
public:
	static double Gravity;
	static double Diameter;
	static double HeavyMass;
	static double LightMass;

	static bool InitConst();

	static bool KillConst();
};