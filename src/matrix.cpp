#include "matrix.hpp"

#define SEGMENT_METHODS(type) \
	LUNAR_METHOD(type, __index), \
	LUNAR_METHOD(type, __newindex)

#define MATRIXBASE_METHODS(type) \
	LUNAR_METHOD(type, __add), \
	LUNAR_METHOD(type, __sub), \
	LUNAR_METHOD(type, __mul), \
	LUNAR_METHOD(type, __div), \
	LUNAR_METHOD(type, __unm), \
	LUNAR_METHOD(type, __len), \
	LUNAR_METHOD(type, __index), \
	LUNAR_METHOD(type, __newindex), \
	LUNAR_METHOD(type, __tostring), \
	LUNAR_METHOD(type, rows), \
	LUNAR_METHOD(type, cols), \
	LUNAR_METHOD(type, size), \
	LUNAR_METHOD(type, data), \
	LUNAR_METHOD(type, setZero), \
	LUNAR_METHOD(type, totable)

#define MATRIX_METHODS(type) \
	MATRIXBASE_METHODS(type), \
	LUNAR_METHOD(type, inverse), \
	LUNAR_METHOD(type, transpose)

#define VECTOR_METHODS(type) \
	MATRIXBASE_METHODS(type), \
	LUNAR_METHOD(type, dot), \
	LUNAR_METHOD(type, norm), \
	LUNAR_METHOD(type, squaredNorm)


namespace LuaEigen {
	template<>
	const char SegmentXf2::className[] = "SegmentXf2";
	template<>
	const LunarType<SegmentXf2>::Reg SegmentXf2::methods[] = {
		SEGMENT_METHODS(SegmentXf2),
		{NULL, NULL}
	};

	template<>
	const char SegmentXf3::className[] = "SegmentXf3";
	template<>
	const LunarType<SegmentXf3>::Reg SegmentXf3::methods[] = {
		SEGMENT_METHODS(SegmentXf3),
		{NULL, NULL}
	};

	template<>
	const char Matrix1f::className[] = "Matrix1f";
	template<>
	const LunarType<Matrix1f>::Reg Matrix1f::methods[] = {
		MATRIX_METHODS(Matrix1f),
		{NULL, NULL}
	};

	template<>
	const char Matrix2f::className[] = "Matrix2f";
	template<>
	const LunarType<Matrix2f>::Reg Matrix2f::methods[] = {
		MATRIX_METHODS(Matrix2f),
		{NULL, NULL}
	};

	template<>
	const char Matrix3f::className[] = "Matrix3f";
	template<>
	const LunarType<Matrix3f>::Reg Matrix3f::methods[] = {
		MATRIX_METHODS(Matrix3f),
		{NULL, NULL}
	};

	template<>
	const char Matrix4f::className[] = "Matrix4f";
	template<>
	const LunarType<Matrix4f>::Reg Matrix4f::methods[] = {
		MATRIX_METHODS(Matrix4f),
		{NULL, NULL}
	};

	template<>
	int MatrixXf::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		float m = lua_tonumberx(L, 3, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 3, "Argument must be a number");
		}
		resize(n, m);
		setZero();
		return 0;
	}
	template<>
	int MatrixXf::init(lua_State *L) {
		Type *o = Lunar<Type>::test(L, 2);
		if (o != nullptr) {
			*this = *o;
		}
		else {
			resize(L);
		}
		return 0;
	}
	template<>
	const char MatrixXf::className[] = "MatrixXf";
	template<>
	const LunarType<MatrixXf>::Reg MatrixXf::methods[] = {
		MATRIX_METHODS(MatrixXf),
		LUNAR_METHOD(MatrixXf, resize),
		{NULL, NULL}
	};

	template<>
	const char Vector2f::className[] = "Vector2f";
	template<>
	const LunarType<Vector2f>::Reg Vector2f::methods[] = {
		VECTOR_METHODS(Vector2f),
		LUNAR_METHOD(Vector2f, x),
		LUNAR_METHOD(Vector2f, y),
		{NULL, NULL}
	};

	template<>
	const char Vector3f::className[] = "Vector3f";
	template<>
	const LunarType<Vector3f>::Reg Vector3f::methods[] = {
		VECTOR_METHODS(Vector3f),
		LUNAR_METHOD(Vector3f, x),
		LUNAR_METHOD(Vector3f, y),
		LUNAR_METHOD(Vector3f, z),
		LUNAR_METHOD(Vector3f, cross),
		{NULL, NULL}
	};

	template<>
	const char Vector4f::className[] = "Vector4f";
	template<>
	const LunarType<Vector4f>::Reg Vector4f::methods[] = {
		VECTOR_METHODS(Vector4f),
		LUNAR_METHOD(Vector4f, x),
		LUNAR_METHOD(Vector4f, y),
		LUNAR_METHOD(Vector4f, z),
		LUNAR_METHOD(Vector4f, w),
		{NULL, NULL}
	};

	template<>
	int VectorXf::prep(lua_State *L) {
		const int instance = lua_absindex(L, -1);
		Lunar<Segment<Type, 2>>::push(L, new Segment<Type, 2>(this), true);
		lua_setfield(L, instance, "segment2");
		Lunar<Segment<Type, 3>>::push(L, new Segment<Type, 3>(this), true);
		lua_setfield(L, instance, "segment3");
		return 0;
	}
	template<>
	int VectorXf::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(n);
		setZero();
		return 0;
	}
	template<>
	int VectorXf::init(lua_State *L) {
		Type *o = Lunar<Type>::test(L, 2);
		if (o != nullptr) {
			*this = *o;
		}
		else {
			resize(L);
		}
		return 0;
	}
	template<>
	const char VectorXf::className[] = "VectorXf";
	template<>
	const LunarType<VectorXf>::Reg VectorXf::methods[] = {
		VECTOR_METHODS(VectorXf),
		LUNAR_METHOD(VectorXf, resize),
		{NULL, NULL}
	};
}
