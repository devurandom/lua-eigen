#include "quaternionf.hpp"

#include "matrix.hpp"

namespace LuaEigen {
	Quaternionf::Quaternionf(lua_State *L)
	: Base()
	{}

	Quaternionf::Quaternionf(const AngleAxisType &o)
	: Base(o)
	{}

	Quaternionf::~Quaternionf()
	{}

	int Quaternionf::init(lua_State *L) {
		float w = luaL_checknumber(L, 2);
		float x = luaL_checknumber(L, 3);
		float y = luaL_checknumber(L, 4);
		float z = luaL_checknumber(L, 5);

		*this = Base(w, x, y, z);

		return 0;
	}


	int Quaternionf::__mul(lua_State *L) {
		Quaternionf *op1q = Lunar<Quaternionf>::test(L, 1);
		if (op1q != nullptr) {
			Quaternionf *op2q = Lunar<Quaternionf>::test(L, 2);
			if (op2q != nullptr) {
				Lunar<Quaternionf>::push(L, new Quaternionf((*op1q) * (*op2q)), true);
				return 1;
			}

			Vector3f *op2v = Lunar<Vector3f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector3f>::push(L, new Vector3f((*op1q) * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Quaternionf or Vector3f");
		}

		return luaL_argerror(L, 1, "Argument must be a Quaternionf");
	}


	int Quaternionf::__tostring(lua_State *L) {
		lua_pushfstring(L, "(%f, %f, %f, %f)", w(), x(), y(), z());
		return 1;
	}


	LUNAR_DEFINE(Quaternionf) {
		LUNAR_METHOD(Quaternionf, __mul),
		LUNAR_METHOD(Quaternionf, __tostring),
		{NULL, NULL}
	};
}
