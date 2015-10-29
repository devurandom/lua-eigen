extern "C" {
#include <lua.h>
#include <lextlib.h>
}

#include <lunar.hpp>

#include <Eigen/Geometry>

#include "angleaxisf.hpp"
#include "quaternionf.hpp"

#include "matrix.hpp"

#include "conjugategradient.hpp"


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

	using LuaEigen::Vector2f;
	using LuaEigen::Vector3f;
	using LuaEigen::Vector4f;
	using LuaEigen::VectorXf;

	using LuaEigen::SegmentXf2;
	using LuaEigen::SegmentXf3;

	using LuaEigen::Vector2Tf;
	using LuaEigen::Vector3Tf;
	using LuaEigen::Vector4Tf;
	using LuaEigen::VectorXTf;

	using LuaEigen::SegmentXTf2;
	using LuaEigen::SegmentXTf3;

	using LuaEigen::Matrix1f;
	using LuaEigen::Matrix2f;
	using LuaEigen::Matrix3f;
	using LuaEigen::Matrix4f;
	using LuaEigen::MatrixXf;

	using LuaEigen::Matrix2Xf;
	using LuaEigen::Matrix3Xf;
	using LuaEigen::Matrix4Xf;

	using LuaEigen::MatrixX2f;
	using LuaEigen::MatrixX3f;
	using LuaEigen::MatrixX4f;

	using LuaEigen::Matrix32f;

	using LuaEigen::Matrix23f;

	using LuaEigen::Matrix24f;
	using LuaEigen::Matrix34f;

	using LuaEigen::Matrix42f;
	using LuaEigen::Matrix43f;

	using LuaEigen::ConjugateGradient1f;
	using LuaEigen::ConjugateGradient2f;
	using LuaEigen::ConjugateGradient3f;
	using LuaEigen::ConjugateGradient4f;
	using LuaEigen::ConjugateGradientXf;

	lua_newtable(L);
	int l_eigen = lua_gettop(L);

	luaL_setfuncs(L, luaeigen_lib, 0);

	Lunar<AngleAxisf>::Register(L);
	Lunar<Quaternionf>::Register(L);

	Lunar<Vector2f>::Register(L);
	Lunar<Vector3f>::Register(L);
	Lunar<Vector4f>::Register(L);
	Lunar<VectorXf>::Register(L);

	Lunar<SegmentXf2>::Register(L);
	Lunar<SegmentXf3>::Register(L);

	Lunar<Vector2Tf>::Register(L);
	Lunar<Vector3Tf>::Register(L);
	Lunar<Vector4Tf>::Register(L);
	Lunar<VectorXTf>::Register(L);

	Lunar<SegmentXTf2>::Register(L);
	Lunar<SegmentXTf3>::Register(L);

	Lunar<Matrix1f>::Register(L);
	Lunar<Matrix2f>::Register(L);
	Lunar<Matrix3f>::Register(L);
	Lunar<Matrix4f>::Register(L);
	Lunar<MatrixXf>::Register(L);

	Lunar<Matrix2Xf>::Register(L);
	Lunar<Matrix3Xf>::Register(L);
	Lunar<Matrix4Xf>::Register(L);

	Lunar<MatrixX2f>::Register(L);
	Lunar<MatrixX3f>::Register(L);
	Lunar<MatrixX4f>::Register(L);

	Lunar<Matrix32f>::Register(L);

	Lunar<Matrix23f>::Register(L);

	Lunar<Matrix24f>::Register(L);
	Lunar<Matrix34f>::Register(L);

	Lunar<Matrix42f>::Register(L);
	Lunar<Matrix43f>::Register(L);

	Lunar<ConjugateGradient1f>::Register(L);
	Lunar<ConjugateGradient2f>::Register(L);
	Lunar<ConjugateGradient3f>::Register(L);
	Lunar<ConjugateGradient4f>::Register(L);
	Lunar<ConjugateGradientXf>::Register(L);

	luaopen_eigen_util(L);
	lua_setfield(L, l_eigen, "util");

	return 1;
}
