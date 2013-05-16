#ifndef LUAEIGEN_QUATERNION_HPP
#define LUAEIGEN_QUATERNION_HPP

#include <Eigen/Geometry>

extern "C" {
#include <lua.h>
}

#include "lunar.hpp"

namespace LuaEigen {
	struct Quaternionf : public Eigen::Quaternionf {
		Quaternionf(lua_State *L);
		Quaternionf(const Eigen::Quaternionf &o);
		~Quaternionf();

		int init(lua_State *L);

		int __mul(lua_State *L);
		int __tostring(lua_State *L);

		LUNAR_DECLARE(Quaternionf);
	};
}

#endif
