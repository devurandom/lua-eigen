extern "C" {
#include <lua.h>
}

#include "lunar.hpp"

#include "matrix4f.hpp"


static float deg2rad(float deg) {
	return deg * M_PI / 180.0f;
}

#if 0
static Eigen::Matrix4f projection(float r, float l, float t, float b, float f, float n) {
	const float w = r-l, h = t-b, d = f-n; // width, height, depth

	Eigen::Matrix4f projection;

	projection <<
		2.0f*n/w , 0.0f     , (r+l)/w     , 0.0f,
		0.0f     , 2.0f*n/h , (t+b)/h     , 0.0f,
		0.0f     , -(f+n)/d , -2.0f*f*n/d , 0.0f,
		0.0f     , 0.0f     , 1.0f        , 0.0f;

	return projection;
}

static Eigen::Matrix4f simple_projection(float fovy, float aspect, float n, float f) {
	const float
		y_scale = tanf(deg2rad(fovy / 2.0f)),
		x_scale = aspect * y_scale;
	const float
		r = y_scale * n,
		t = x_scale * n;

	return projection(r, -r, t, -t, f, n);
}
#endif

static Eigen::Matrix4f more_simple_projection(float fovy, float aspect, float n, float f) {
	const float
		y_scale = 1.0f/tanf(deg2rad(fovy / 2.0f)),
		x_scale = y_scale / aspect,
		d = f - n;

	Eigen::Matrix4f out;
	out <<
		x_scale, 0.0f, 0.0f, 0.0f,
		0.0f, y_scale, 0.0f, 0.0f,
		0.0f, -((f + n) / d), -((2.0f*n*f)/d), 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f;

	return out;
}


static int create_projection(lua_State *L) {
	using LuaEigen::Matrix4f;

	const int l_args = 1;

	luaL_checktype(L, l_args, LUA_TTABLE);

	lua_getfield(L, l_args, "fovy"); // [-0,+1,e]
	float fovy = luaX_checknumber(L, -1, "fovy");

	lua_getfield(L, l_args, "aspect"); // [-0,+1,e]
	float aspect = luaX_checknumber(L, -1, "aspect");

	lua_getfield(L, l_args, "near"); // [-0,+1,e]
	float near = luaX_checknumber(L, -1, "near");

	lua_getfield(L, l_args, "far"); // [-0,+1,e]
	float far = luaX_checknumber(L, -1, "far");

	Lunar<Matrix4f>::push(L, new Matrix4f(more_simple_projection(fovy, aspect, near, far)), true);

	return 1;
}


static luaL_Reg eigen_util_lib[] = {
	LUAX_FUNCTION(, create_projection),
	{NULL, NULL}
};


extern "C" int luaopen_eigen_util(lua_State *L) {
	lua_newlib(L, eigen_util_lib);

	return 1;
}
