#ifndef LUAEIGEN_ANGLEAXISF_HPP
#define LUAEIGEN_ANGLEAXISF_HPP

#include <Eigen/Geometry>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct AngleAxisf : public Eigen::AngleAxisf {
		typedef Eigen::AngleAxisf Base;

		AngleAxisf(lua_State *L);
		AngleAxisf(const Base &o);
		template<typename Derived>
		AngleAxisf(const Eigen::QuaternionBase<Derived> &o) : Base(o) {}
		template<typename Derived>
		AngleAxisf(const Eigen::MatrixBase<Derived> &o) : Base(o) {}
		~AngleAxisf();

		template<typename Derived>
		AngleAxisf &operator=(const Eigen::QuaternionBase<Derived> &o) {
			return Base::operator=(o);
		}

		template<typename Derived>
		AngleAxisf &operator=(const Eigen::MatrixBase<Derived> &o) {
			return Base::operator=(o);
		}

		int init(lua_State *L);

		int __mul(lua_State *L);
		int __tostring(lua_State *L);

		LUNAR_DECLARE(AngleAxisf);
	};
}

#endif
