#ifndef LUAEIGEN_MATRIX2F_HPP
#define LUAEIGEN_MATRIX2F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include "lunar.hpp"

namespace LuaEigen {
	struct Matrix2f : public Eigen::Matrix2f {
		using Eigen::Matrix2f::data;
		using Eigen::Matrix2f::setZero;

		Matrix2f(lua_State *L);
		Matrix2f(const Eigen::Matrix2f &o);
		~Matrix2f();

		int init(lua_State *L);

		int __add(lua_State *L);
		int __sub(lua_State *L);
		int __mul(lua_State *L);
		int __unm(lua_State *L);
		int __tostring(lua_State *L);

		int data(lua_State *L);
		int setZero(lua_State *L);

		LUNAR_DECLARE(Matrix2f);
	};
}

#endif
