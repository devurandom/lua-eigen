#include "vector3f.hpp"

#include <iostream>

#include <Eigen/Geometry>

#include "matrix3f.hpp"

namespace LuaEigen {
	Vector3f::Vector3f(lua_State *L)
	{}

	Vector3f::Vector3f(const Eigen::Vector3f &o)
	: Eigen::Vector3f(o)
	{}

	Vector3f::~Vector3f()
	{}


	int Vector3f::init(lua_State *L) {
		int l_nargs = lua_gettop(L);

		if (l_nargs == 1) {
			setZero();
		}
		if (l_nargs-1 == size()) {
			for (int i = 2; i <= l_nargs; i++) {
				int isnum = false;
				float n = lua_tonumberx(L, i, &isnum);
				if (!isnum) {
					return luaL_argerror(L, i, "Argument must be a number");
				}
				(*this)((i-2)/cols(),(i-2)%cols()) = n;
			}
		}

		return 0;
	}


	int Vector3f::__add(lua_State *L) {
		Vector3f *op1v = Lunar<Vector3f>::check(L, 1);
		Vector3f *op2v = Lunar<Vector3f>::check(L, 2);
		Lunar<Vector3f>::push(L, new Vector3f((*op1v) + (*op2v)), true);
		return 1;
	}


	int Vector3f::__sub(lua_State *L) {
		Vector3f *op1v = Lunar<Vector3f>::check(L, 1);
		Vector3f *op2v = Lunar<Vector3f>::check(L, 2);
		Lunar<Vector3f>::push(L, new Vector3f((*op1v) - (*op2v)), true);
		return 1;
	}


	int Vector3f::__mul(lua_State *L) {
		Matrix3f *op1m = Lunar<Matrix3f>::test(L, 1);
		if (op1m != nullptr) {
			Vector3f *op2v = Lunar<Vector3f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector3f>::push(L, new Vector3f((*op1m) * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector3f, because argument #1 was a Matrix3f");
		}

		Vector3f *op1v = Lunar<Vector3f>::test(L, 1);
		if (op1v != nullptr) {
			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Vector3f>::push(L, new Vector3f((*op1v) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a number, because argument #1 was a Vector3f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Vector3f *op2v = Lunar<Vector3f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector3f>::push(L, new Vector3f(op1s * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector3f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix3f, Vector3f or a number");
	}


	int Vector3f::__div(lua_State *L) {
		Vector3f *op1v = Lunar<Vector3f>::check(L, 1);
		float op2s = luaL_checknumber(L, 2);
		Lunar<Vector3f>::push(L, new Vector3f((*op1v) / op2s), true);
		return 1;
	}


	int Vector3f::__unm(lua_State *L) {
		Lunar<Vector3f>::push(L, new Vector3f(-(*this)), true);
		return 1;
	}


	int Vector3f::__tostring(lua_State *L) {
		lua_pushfstring(L, "(%f, %f, %f)", x(), y(), z());
		return 1;
	}


	int Vector3f::x(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			x() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, x());
		return 1;
	}


	int Vector3f::y(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			y() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, y());
		return 1;
	}


	int Vector3f::z(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			z() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, z());
		return 1;
	}


	int Vector3f::dot(lua_State *L) {
		Vector3f *o = Lunar<Vector3f>::check(L, 2);
		lua_pushnumber(L, dot(*o));
		return 1;
	}


	int Vector3f::cross(lua_State *L) {
		Vector3f *o = Lunar<Vector3f>::check(L, 2);
		Lunar<Vector3f>::push(L, new Vector3f(cross(*o)), true);
		return 1;
	}


	int Vector3f::norm(lua_State *L) {
		lua_pushnumber(L, norm());
		return 1;
	}


	int Vector3f::squaredNorm(lua_State *L) {
		lua_pushnumber(L, squaredNorm());
		return 1;
	}


	int Vector3f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Vector3f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	LUNAR_DEFINE(Vector3f) {
		LUNAR_METHOD(Vector3f, __add),
		LUNAR_METHOD(Vector3f, __sub),
		LUNAR_METHOD(Vector3f, __mul),
		LUNAR_METHOD(Vector3f, __div),
		LUNAR_METHOD(Vector3f, __unm),
		LUNAR_METHOD(Vector3f, __tostring),
		LUNAR_METHOD(Vector3f, x),
		LUNAR_METHOD(Vector3f, y),
		LUNAR_METHOD(Vector3f, z),
		LUNAR_METHOD(Vector3f, data),
		LUNAR_METHOD(Vector3f, setZero),
		LUNAR_METHOD(Vector3f, dot),
		LUNAR_METHOD(Vector3f, cross),
		LUNAR_METHOD(Vector3f, norm),
		LUNAR_METHOD(Vector3f, squaredNorm),
		{NULL, NULL}
	};
}
