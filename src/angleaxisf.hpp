#ifndef LUAEIGEN_ANGLEAXISF_HPP
#define LUAEIGEN_ANGLEAXISF_HPP

#include <Eigen/Geometry>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct AngleAxisf : public Eigen::AngleAxisf {
		AngleAxisf(lua_State *L);
		AngleAxisf(const Eigen::AngleAxisf &o);
		~AngleAxisf();

		int init(lua_State *L);

		int __mul(lua_State *L);
		int __tostring(lua_State *L);

		LUNAR_DECLARE(AngleAxisf);
	};
}

#endif
