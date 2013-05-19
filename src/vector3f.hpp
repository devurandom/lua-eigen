#ifndef LUAEIGEN_VECTOR3F_HPP
#define LUAEIGEN_VECTOR3F_HPP

#include <Eigen/Core>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Vector3f : public Eigen::Vector3f {
		using Eigen::Vector3f::x;
		using Eigen::Vector3f::y;
		using Eigen::Vector3f::z;
		using Eigen::Vector3f::data;
		using Eigen::Vector3f::setZero;
		using Eigen::Vector3f::dot;
		using Eigen::Vector3f::cross;
		using Eigen::Vector3f::norm;
		using Eigen::Vector3f::squaredNorm;

		Vector3f(lua_State *L);
		Vector3f(const Eigen::Vector3f &o);
		~Vector3f();

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

		int data(lua_State *L);
		int setZero(lua_State *L);

		int dot(lua_State *L);
		int cross(lua_State *L);

		int norm(lua_State *L);
		int squaredNorm(lua_State *L);

		LUNAR_DECLARE(Vector3f);
	};
}

#endif
