#ifndef LUAEIGEN_VECTOR4F_HPP
#define LUAEIGEN_VECTOR4F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Vector4f : public Eigen::Vector4f {
		using Eigen::Vector4f::x;
		using Eigen::Vector4f::y;
		using Eigen::Vector4f::z;
		using Eigen::Vector4f::w;
		using Eigen::Vector4f::data;
		using Eigen::Vector4f::setZero;
		using Eigen::Vector4f::dot;
		using Eigen::Vector4f::norm;
		using Eigen::Vector4f::squaredNorm;

		Vector4f(lua_State *L);
		Vector4f(const Eigen::Vector4f &o);
		~Vector4f();

		int init(lua_State *L);

		int __add(lua_State *L);
		int __sub(lua_State *L);
		int __mul(lua_State *L);
		int __div(lua_State *L);
		int __unm(lua_State *L);
		int __tostring(lua_State *L);

		int x(lua_State *L);
		int y(lua_State *L);
		int z(lua_State *L);
		int w(lua_State *L);

		int data(lua_State *L);
		int setZero(lua_State *L);

		int dot(lua_State *L);

		int norm(lua_State *L);
		int squaredNorm(lua_State *L);

		LUNAR_DECLARE(Vector4f);
	};
}

#endif
