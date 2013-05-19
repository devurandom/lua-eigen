extern "C" {
#include <lua.h>
#include "lextlib.h"
}

#include <Eigen/Geometry>

#include "lunar.hpp"

#include "angleaxisf.hpp"
#include "quaternionf.hpp"

#include "matrix2f.hpp"
#include "matrix3f.hpp"
#include "matrix4f.hpp"

#include "vector2f.hpp"
#include "vector3f.hpp"
#include "vector4f.hpp"


extern "C" int luaopen_eigen_util(lua_State *L);


static int AffineTranslation3f(lua_State *L) {
	using LuaEigen::Matrix4f;
	using LuaEigen::Vector3f;

	Vector3f *pos = Lunar<Vector3f>::check(L, 1);
	Matrix4f *matrix = new Matrix4f(
		Eigen::Affine3f(
			Eigen::Translation3f(*pos)
		).matrix()
	);
	Lunar<Matrix4f>::push(L, matrix, true);
	return 1;
}


static int AffineEulerAngle2fAndTranslation3f(lua_State *L) {
	using LuaEigen::Matrix4f;
	using LuaEigen::Vector2f;
	using LuaEigen::Vector3f;

	Vector3f *position = Lunar<Vector3f>::check(L, 1);
	Vector2f *rotation = Lunar<Vector2f>::check(L, 2);

	Matrix4f *matrix = new Matrix4f(
		Eigen::Affine3f(
			Eigen::AngleAxisf(rotation->x(), Eigen::Vector3f(1.0f, 0.0f, 0.0f))
			* Eigen::AngleAxisf(rotation->y(), Eigen::Vector3f(0.0f, 1.0f, 0.0f))
			* Eigen::Translation3f(*position)
		).matrix()
	);
	Lunar<Matrix4f>::push(L, matrix, true);
	return 1;
}


static luaL_Reg luaeigen_lib[] = {
	LUAX_FUNCTION(, AffineTranslation3f),
	LUAX_FUNCTION(, AffineEulerAngle2fAndTranslation3f),
	{NULL, NULL}
};


extern "C" int luaopen_eigen(lua_State *L) {
	using LuaEigen::AngleAxisf;
	using LuaEigen::Quaternionf;

	using LuaEigen::Matrix2f;
	using LuaEigen::Matrix3f;
	using LuaEigen::Matrix4f;

	using LuaEigen::Vector2f;
	using LuaEigen::Vector3f;
	using LuaEigen::Vector4f;

	lua_newtable(L);
	int l_eigen = lua_gettop(L);

	luaL_setfuncs(L, luaeigen_lib, 0);

	Lunar<AngleAxisf>::Register(L);
	Lunar<Quaternionf>::Register(L);

	Lunar<Matrix2f>::Register(L);
	Lunar<Matrix3f>::Register(L);
	Lunar<Matrix4f>::Register(L);

	Lunar<Vector2f>::Register(L);
	Lunar<Vector3f>::Register(L);
	Lunar<Vector4f>::Register(L);

	luaopen_eigen_util(L);
	lua_setfield(L, l_eigen, "util");

	return 1;
}
