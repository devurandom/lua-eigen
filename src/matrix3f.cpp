#include "matrix3f.hpp"

#include <sstream>

#include <Eigen/Dense>

#include "vector3f.hpp"


namespace LuaEigen {
	Matrix3f::Matrix3f(lua_State *L)
	{}

	Matrix3f::Matrix3f(const Eigen::Matrix3f &o)
	: Eigen::Matrix3f(o)
	{}

	Matrix3f::~Matrix3f()
	{}


	int Matrix3f::init(lua_State *L) {
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


	int Matrix3f::__add(lua_State *L) {
		Matrix3f *op1m = Lunar<Matrix3f>::check(L, 1);
		Matrix3f *op2m = Lunar<Matrix3f>::check(L, 2);
		Lunar<Matrix3f>::push(L, new Matrix3f((*op1m) + (*op2m)), true);
		return 1;
	}


	int Matrix3f::__sub(lua_State *L) {
		Matrix3f *op1m = Lunar<Matrix3f>::check(L, 1);
		Matrix3f *op2m = Lunar<Matrix3f>::check(L, 2);
		Lunar<Matrix3f>::push(L, new Matrix3f((*op1m) - (*op2m)), true);
		return 1;
	}


	int Matrix3f::__mul(lua_State *L) {
		Matrix3f *op1m = Lunar<Matrix3f>::test(L, 1);
		if (op1m != nullptr) {
			Matrix3f *op2m = Lunar<Matrix3f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix3f>::push(L, new Matrix3f((*op1m) * (*op2m)), true);
				return 1;
			}

			Vector3f *op2v = Lunar<Vector3f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector3f>::push(L, new Vector3f((*op1m) * (*op2v)), true);
				return 1;
			}

			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Matrix3f>::push(L, new Matrix3f((*op1m) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix3f, Vector3f or a number, because argument #1 was a Matrix3f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Matrix3f *op2m = Lunar<Matrix3f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix3f>::push(L, new Matrix3f(op1s * (*op2m)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix3f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix3f, Vector3f or a number");
	}


	int Matrix3f::__unm(lua_State *L) {
		Lunar<Matrix3f>::push(L, new Matrix3f(-(*this)), true);
		return 1;
	}


	int Matrix3f::__tostring(lua_State *L) {
		std::stringstream ss;

		ss << *this;
		lua_pushstring(L, ss.str().c_str());

		return 1;
	}


	int Matrix3f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Matrix3f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	int Matrix3f::inverse(lua_State *L) {
		Lunar<Matrix3f>::push(L, new Matrix3f(inverse()), true);
		return 1;
	}


	int Matrix3f::transpose(lua_State *L) {
		Lunar<Matrix3f>::push(L, new Matrix3f(transpose()), true);
		return 1;
	}


	LUNAR_DEFINE(Matrix3f) {
		LUNAR_METHOD(Matrix3f, __add),
		LUNAR_METHOD(Matrix3f, __sub),
		LUNAR_METHOD(Matrix3f, __mul),
		LUNAR_METHOD(Matrix3f, __unm),
		LUNAR_METHOD(Matrix3f, __tostring),
		LUNAR_METHOD(Matrix3f, data),
		LUNAR_METHOD(Matrix3f, setZero),
		LUNAR_METHOD(Matrix3f, inverse),
		LUNAR_METHOD(Matrix3f, transpose),
		{NULL, NULL}
	};
}
