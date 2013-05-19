#ifndef LUAEIGEN_VECTOR2F_HPP
#define LUAEIGEN_VECTOR2F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Vector2f : public Eigen::Vector2f {
		using Eigen::Vector2f::x;
		using Eigen::Vector2f::y;
		using Eigen::Vector2f::data;
		using Eigen::Vector2f::setZero;
		using Eigen::Vector2f::dot;
		using Eigen::Vector2f::norm;
		using Eigen::Vector2f::squaredNorm;

		Vector2f(lua_State *L);
		Vector2f(const Eigen::Vector2f &o);
		~Vector2f();

		int init(lua_State *L);

		int __add(lua_State *L);
		int __sub(lua_State *L);
		int __mul(lua_State *L);
		int __div(lua_State *L);
		int __unm(lua_State *L);
		int __tostring(lua_State *L);

		int x(lua_State *L);
		int y(lua_State *L);

		int data(lua_State *L);
		int setZero(lua_State *L);

		int dot(lua_State *L);

		int norm(lua_State *L);
		int squaredNorm(lua_State *L);

		LUNAR_DECLARE(Vector2f);
	};
}

#endif
