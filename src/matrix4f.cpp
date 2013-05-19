#include "matrix4f.hpp"

#include <sstream>

#include <Eigen/Dense>

#include "vector4f.hpp"


namespace LuaEigen {
	Matrix4f::Matrix4f(lua_State *L)
	{}

	Matrix4f::Matrix4f(const Eigen::Matrix4f &o)
	: Eigen::Matrix4f(o)
	{}

	Matrix4f::~Matrix4f()
	{}


	int Matrix4f::init(lua_State *L) {
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


	int Matrix4f::__add(lua_State *L) {
		Matrix4f *op1m = Lunar<Matrix4f>::check(L, 1);
		Matrix4f *op2m = Lunar<Matrix4f>::check(L, 2);
		Lunar<Matrix4f>::push(L, new Matrix4f((*op1m) + (*op2m)), true);
		return 1;
	}


	int Matrix4f::__sub(lua_State *L) {
		Matrix4f *op1m = Lunar<Matrix4f>::check(L, 1);
		Matrix4f *op2m = Lunar<Matrix4f>::check(L, 2);
		Lunar<Matrix4f>::push(L, new Matrix4f((*op1m) - (*op2m)), true);
		return 1;
	}


	int Matrix4f::__mul(lua_State *L) {
		Matrix4f *op1m = Lunar<Matrix4f>::test(L, 1);
		if (op1m != nullptr) {
			Matrix4f *op2m = Lunar<Matrix4f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix4f>::push(L, new Matrix4f((*op1m) * (*op2m)), true);
				return 1;
			}

			Vector4f *op2v = Lunar<Vector4f>::test(L, 2);
			if (op2v != nullptr) {
				Lunar<Vector4f>::push(L, new Vector4f((*op1m) * (*op2v)), true);
				return 1;
			}

			int isnum = false;
			float op2s = lua_tonumberx(L, 2, &isnum);
			if (isnum) {
				Lunar<Matrix4f>::push(L, new Matrix4f((*op1m) * op2s), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix4f, Vector4f or a number, because argument #1 was a Matrix4f");
		}

		int isnum = false;
		float op1s = lua_tonumberx(L, 1, &isnum);
		if (isnum) {
			Matrix4f *op2m = Lunar<Matrix4f>::test(L, 2);
			if (op2m != nullptr) {
				Lunar<Matrix4f>::push(L, new Matrix4f(op1s * (*op2m)), true);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument must be a Matrix4f, because argument #1 was a scalar");
		}

		return luaL_argerror(L, 1, "Argument must be a Matrix4f, Vector4f or a number");
	}


	int Matrix4f::__unm(lua_State *L) {
		Lunar<Matrix4f>::push(L, new Matrix4f(-(*this)), true);
		return 1;
	}


	int Matrix4f::__tostring(lua_State *L) {
		std::stringstream ss;

		ss << *this;
		lua_pushstring(L, ss.str().c_str());

		return 1;
	}


	int Matrix4f::data(lua_State *L) {
		lua_pushlightuserdata(L, data());
		return 1;
	}


	int Matrix4f::setZero(lua_State *L) {
		setZero();
		return 0;
	}


	int Matrix4f::inverse(lua_State *L) {
		Lunar<Matrix4f>::push(L, new Matrix4f(inverse()), true);
		return 1;
	}


	int Matrix4f::transpose(lua_State *L) {
		Lunar<Matrix4f>::push(L, new Matrix4f(transpose()), true);
		return 1;
	}


	LUNAR_DEFINE(Matrix4f) {
		LUNAR_METHOD(Matrix4f, __add),
		LUNAR_METHOD(Matrix4f, __sub),
		LUNAR_METHOD(Matrix4f, __mul),
		LUNAR_METHOD(Matrix4f, __unm),
		LUNAR_METHOD(Matrix4f, __tostring),
		LUNAR_METHOD(Matrix4f, data),
		LUNAR_METHOD(Matrix4f, setZero),
		LUNAR_METHOD(Matrix4f, inverse),
		LUNAR_METHOD(Matrix4f, transpose),
		{NULL, NULL}
	};
}
