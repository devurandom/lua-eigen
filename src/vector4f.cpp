#include "vector4f.hpp"

#include <Eigen/Geometry>

#include "matrix4f.hpp"

namespace LuaEigen {
	Vector4f::Vector4f(lua_State *L)
	{}

	Vector4f::Vector4f(const Eigen::Vector4f &o)
	: Eigen::Vector4f(o)
	{}

	Vector4f::~Vector4f()
	{}


	int Vector4f::init(lua_State *L) {
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


	int Vector4f::__add(lua_State *L) {
		Vector4f *op1v = Lunar<Vector4f>::check(L, 1);
		Vector4f *op2v = Lunar<Vector4f>::check(L, 2);
		Lunar<Vector4f>::push(L, new Vector4f((*op1v) + (*op2v)), true);
		return 1;
	}


	int Vector4f::__sub(lua_State *L) {
		Vector4f *op1v = Lunar<Vector4f>::check(L, 1);
		Vector4f *op2v = Lunar<Vector4f>::check(L, 2);
		Lunar<Vector4f>::push(L, new Vector4f((*op1v) - (*op2v)), true);
		return 1;
	}


	int Vector4f::__mul(lua_State *L) {
		Matrix4f *op1m = Lunar<Matrix4f>::test(L, 1);
		if (op1m != nullptr) {
			Vector4f *op2v = Lunar<Vector4f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector4f>::push(L, new Vector4f((*op1m) * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector4f, because argument #1 was a Matrix4f");
		}

		Vector4f *op1v = Lunar<Vector4f>::test(L, 1);
		if (op1v != nullptr) {
			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Vector4f>::push(L, new Vector4f((*op1v) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a number, because argument #1 was a Vector4f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Vector4f *op2v = Lunar<Vector4f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector4f>::push(L, new Vector4f(op1s * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector4f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix4f, Vector4f or a number");
	}


	int Vector4f::__div(lua_State *L) {
		Vector4f *op1v = Lunar<Vector4f>::check(L, 1);
		float op2s = luaL_checknumber(L, 2);
		Lunar<Vector4f>::push(L, new Vector4f((*op1v) / op2s), true);
		return 1;
	}


	int Vector4f::__unm(lua_State *L) {
		Lunar<Vector4f>::push(L, new Vector4f(-(*this)), true);
		return 1;
	}


	int Vector4f::__tostring(lua_State *L) {
		lua_pushfstring(L, "(%f, %f, %f, %f)", x(), y(), z(), w());
		return 1;
	}


	int Vector4f::x(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			x() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, x());
		return 1;
	}


	int Vector4f::y(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			y() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, y());
		return 1;
	}


	int Vector4f::z(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			z() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, z());
		return 1;
	}


	int Vector4f::w(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			w() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, w());
		return 1;
	}


	int Vector4f::dot(lua_State *L) {
		Vector4f *o = Lunar<Vector4f>::check(L, 2);
		lua_pushnumber(L, dot(*o));
		return 1;
	}


	int Vector4f::norm(lua_State *L) {
		lua_pushnumber(L, norm());
		return 1;
	}


	int Vector4f::squaredNorm(lua_State *L) {
		lua_pushnumber(L, squaredNorm());
		return 1;
	}


	int Vector4f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Vector4f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	LUNAR_DEFINE(Vector4f) {
		LUNAR_METHOD(Vector4f, __add),
		LUNAR_METHOD(Vector4f, __sub),
		LUNAR_METHOD(Vector4f, __mul),
		LUNAR_METHOD(Vector4f, __div),
		LUNAR_METHOD(Vector4f, __unm),
		LUNAR_METHOD(Vector4f, __tostring),
		LUNAR_METHOD(Vector4f, x),
		LUNAR_METHOD(Vector4f, y),
		LUNAR_METHOD(Vector4f, z),
		LUNAR_METHOD(Vector4f, w),
		LUNAR_METHOD(Vector4f, data),
		LUNAR_METHOD(Vector4f, setZero),
		LUNAR_METHOD(Vector4f, dot),
		LUNAR_METHOD(Vector4f, norm),
		LUNAR_METHOD(Vector4f, squaredNorm),
		{NULL, NULL}
	};
}
