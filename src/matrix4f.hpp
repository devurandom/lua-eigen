#ifndef LUAEIGEN_MATRIX4F_HPP
#define LUAEIGEN_MATRIX4F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Matrix4f : public Eigen::Matrix4f {
		using Eigen::Matrix4f::data;
		using Eigen::Matrix4f::setZero;
		using Eigen::Matrix4f::inverse;
		using Eigen::Matrix4f::transpose;

		Matrix4f(lua_State *L);
		Matrix4f(const Eigen::Matrix4f &o);
		~Matrix4f();

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

		LUNAR_DECLARE(Matrix4f);
	};
}

#endif
