#include "angleaxisf.hpp"

#include "quaternionf.hpp"
#include "matrix.hpp"

namespace LuaEigen {
	AngleAxisf::AngleAxisf(lua_State *L)
	{}

	AngleAxisf::AngleAxisf(const Base &o)
	: Base(o)
	{}

	AngleAxisf::~AngleAxisf()
	{}


	int AngleAxisf::init(lua_State *L) {
		float angle = luaL_checknumber(L, 2);
		Vector3f *axis = Lunar<Vector3f>::check(L, 3);

		*this = Eigen::AngleAxisf(angle, *axis);

		return 0;
	}


	int AngleAxisf::__mul(lua_State *L) {
		AngleAxisf *op1a = Lunar<AngleAxisf>::test(L, 1);
		if (op1a != nullptr) {
			AngleAxisf *op2a = Lunar<AngleAxisf>::test(L, 2);
			if (op2a != nullptr) {
				Lunar<Quaternionf>::push(L, new Quaternionf((*op1a) * (*op2a)), true);
				return 1;
			}

			Vector3f *op2v = Lunar<Vector3f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector3f>::push(L, new Vector3f((*op1a) * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a AngleAxisf or Vector3f");
		}

		return luaL_argerror(L, 1, "Argument must be a AngleAxisf");
	}


	int AngleAxisf::__tostring(lua_State *L) {
		lua_pushstring(L, "?");
		return 1;
	}


	LUNAR_DEFINE(AngleAxisf) {
		LUNAR_METHOD(AngleAxisf, __mul),
		LUNAR_METHOD(AngleAxisf, __tostring),
		{NULL, NULL}
	};
}
