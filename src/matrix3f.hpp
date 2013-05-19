#ifndef LUAEIGEN_MATRIX3F_HPP
#define LUAEIGEN_MATRIX3F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Matrix3f : public Eigen::Matrix3f {
		using Eigen::Matrix3f::data;
		using Eigen::Matrix3f::setZero;
		using Eigen::Matrix3f::inverse;
		using Eigen::Matrix3f::transpose;

		Matrix3f(lua_State *L);
		Matrix3f(const Eigen::Matrix3f &o);
		~Matrix3f();

		int init(lua_State *L);

		int __add(lua_State *L);
		int __sub(lua_State *L);
		int __mul(lua_State *L);
		int __unm(lua_State *L);
		int __tostring(lua_State *L);

		int data(lua_State *L);
		int setZero(lua_State *L);

		int inverse(lua_State *L);
		int transpose(lua_State *L);

		LUNAR_DECLARE(Matrix3f);
	};
}

#endif
