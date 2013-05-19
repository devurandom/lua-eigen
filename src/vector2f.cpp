#include "vector2f.hpp"

#include "matrix2f.hpp"


namespace LuaEigen {
	Vector2f::Vector2f(lua_State *L)
	{}

	Vector2f::Vector2f(const Eigen::Vector2f &o)
	: Eigen::Vector2f(o)
	{}

	Vector2f::~Vector2f()
	{}


	int Vector2f::init(lua_State *L) {
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


	int Vector2f::__add(lua_State *L) {
		Vector2f *op1v = Lunar<Vector2f>::check(L, 1);
		Vector2f *op2v = Lunar<Vector2f>::check(L, 2);
		Lunar<Vector2f>::push(L, new Vector2f((*op1v) + (*op2v)), true);
		return 1;
	}


	int Vector2f::__sub(lua_State *L) {
		Vector2f *op1v = Lunar<Vector2f>::check(L, 1);
		Vector2f *op2v = Lunar<Vector2f>::check(L, 2);
		Lunar<Vector2f>::push(L, new Vector2f((*op1v) - (*op2v)), true);
		return 1;
	}


	int Vector2f::__mul(lua_State *L) {
		Matrix2f *op1m = Lunar<Matrix2f>::test(L, 1);
		if (op1m != nullptr) {
			Vector2f *op2v = Lunar<Vector2f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector2f>::push(L, new Vector2f((*op1m) * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector2f, because argument #1 was a Matrix2f");
		}

		Vector2f *op1v = Lunar<Vector2f>::test(L, 1);
		if (op1v != nullptr) {
			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Vector2f>::push(L, new Vector2f((*op1v) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a number, because argument #1 was a Vector2f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Vector2f *op2v = Lunar<Vector2f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector2f>::push(L, new Vector2f(op1s * (*op2v)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Vector2f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix2f, Vector2f or a number");
	}


	int Vector2f::__div(lua_State *L) {
		Vector2f *op1v = Lunar<Vector2f>::check(L, 1);
		float op2s = luaL_checknumber(L, 2);
		Lunar<Vector2f>::push(L, new Vector2f((*op1v) / op2s), true);
		return 1;
	}


	int Vector2f::__unm(lua_State *L) {
		Lunar<Vector2f>::push(L, new Vector2f(-(*this)), true);
		return 1;
	}


	int Vector2f::__tostring(lua_State *L) {
		lua_pushfstring(L, "(%f, %f)", x(), y());
		return 1;
	}


	int Vector2f::x(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			x() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, x());
		return 1;
	}


	int Vector2f::y(lua_State *L) {
		int nargs = lua_gettop(L);

		if (nargs > 1) {
			y() = luaL_checknumber(L, 2);
			return 0;
		}

		lua_pushnumber(L, y());
		return 1;
	}


	int Vector2f::dot(lua_State *L) {
		Vector2f *o = Lunar<Vector2f>::check(L, 2);
		lua_pushnumber(L, dot(*o));
		return 1;
	}


	int Vector2f::norm(lua_State *L) {
		lua_pushnumber(L, norm());
		return 1;
	}


	int Vector2f::squaredNorm(lua_State *L) {
		lua_pushnumber(L, squaredNorm());
		return 1;
	}


	int Vector2f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Vector2f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	LUNAR_DEFINE(Vector2f) {
		LUNAR_METHOD(Vector2f, __add),
		LUNAR_METHOD(Vector2f, __sub),
		LUNAR_METHOD(Vector2f, __mul),
		LUNAR_METHOD(Vector2f, __div),
		LUNAR_METHOD(Vector2f, __unm),
		LUNAR_METHOD(Vector2f, __tostring),
		LUNAR_METHOD(Vector2f, x),
		LUNAR_METHOD(Vector2f, y),
		LUNAR_METHOD(Vector2f, data),
		LUNAR_METHOD(Vector2f, setZero),
		LUNAR_METHOD(Vector2f, dot),
		LUNAR_METHOD(Vector2f, norm),
		LUNAR_METHOD(Vector2f, squaredNorm),
		{NULL, NULL}
	};
}
