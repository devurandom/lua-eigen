#include "matrix2f.hpp"

#include <sstream>

#include "vector2f.hpp"

namespace LuaEigen {
	Matrix2f::Matrix2f(lua_State *L)
	{}

	Matrix2f::Matrix2f(const Eigen::Matrix2f &o)
	: Eigen::Matrix2f(o)
	{}

	Matrix2f::~Matrix2f()
	{}


	int Matrix2f::init(lua_State *L) {
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


	int Matrix2f::__add(lua_State *L) {
		Matrix2f *op1m = Lunar<Matrix2f>::check(L, 1);
		Matrix2f *op2m = Lunar<Matrix2f>::check(L, 2);
		Lunar<Matrix2f>::push(L, new Matrix2f((*op1m) + (*op2m)), true);
		return 1;
	}


	int Matrix2f::__sub(lua_State *L) {
		Matrix2f *op1m = Lunar<Matrix2f>::check(L, 1);
		Matrix2f *op2m = Lunar<Matrix2f>::check(L, 2);
		Lunar<Matrix2f>::push(L, new Matrix2f((*op1m) - (*op2m)), true);
		return 1;
	}


	int Matrix2f::__mul(lua_State *L) {
		Matrix2f *op1m = Lunar<Matrix2f>::test(L, 1);
		if (op1m != nullptr) {
			Matrix2f *op2m = Lunar<Matrix2f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix2f>::push(L, new Matrix2f((*op1m) * (*op2m)), true);
				return 1;
			}

			Vector2f *op2v = Lunar<Vector2f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector2f>::push(L, new Vector2f((*op1m) * (*op2v)), true);
				return 1;
			}

			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Matrix2f>::push(L, new Matrix2f((*op1m) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix2f, Vector2f or a number, because argument #1 was a Matrix2f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Matrix2f *op2m = Lunar<Matrix2f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix2f>::push(L, new Matrix2f(op1s * (*op2m)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix2f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix2f or a number");
	}


	int Matrix2f::__unm(lua_State *L) {
		Lunar<Matrix2f>::push(L, new Matrix2f(-(*this)), true);
		return 1;
	}


	int Matrix2f::__tostring(lua_State *L) {
		std::stringstream ss;

		ss << *this;
		lua_pushstring(L, ss.str().c_str());

		return 1;
	}


	int Matrix2f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Matrix2f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	LUNAR_DEFINE(Matrix2f) {
		LUNAR_METHOD(Matrix2f, __add),
		LUNAR_METHOD(Matrix2f, __sub),
		LUNAR_METHOD(Matrix2f, __mul),
		LUNAR_METHOD(Matrix2f, __unm),
		LUNAR_METHOD(Matrix2f, __tostring),
		LUNAR_METHOD(Matrix2f, data),
		LUNAR_METHOD(Matrix2f, setZero),
		{NULL, NULL}
	};
}
