#ifndef LUAEIGEN_QUATERNIONF_HPP
#define LUAEIGEN_QUATERNIONF_HPP

#include <Eigen/Geometry>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	struct Quaternionf : public Eigen::Quaternionf {
		typedef Eigen::Quaternionf Base;
		typedef typename Base::AngleAxisType AngleAxisType;

		Quaternionf(lua_State *L);
		Quaternionf(const AngleAxisType &o);
		template<typename Derived>
		Quaternionf(const Eigen::QuaternionBase<Derived> &o) : Base(o) {}
		template<typename Derived>
		Quaternionf(const Eigen::MatrixBase<Derived> &o) : Base(o) {}
		~Quaternionf();

		int oninit(lua_State *L);

		int __mul(lua_State *L);
		int __tostring(lua_State *L);

		LUNAR_DECLARE(Quaternionf);
	};
}

#endif
