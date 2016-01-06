#include "matrix.hpp"

#define SEGMENT_METHODS(type) \
	LUNAR_METHOD(type, __index), \
	LUNAR_METHOD(type, __newindex)

#define MATRIXBASE_METHODS(type) \
	LUNAR_METHOD(type, __call), \
	LUNAR_METHOD(type, __add), \
	LUNAR_METHOD(type, __sub), \
	LUNAR_METHOD(type, __mul), \
	LUNAR_METHOD(type, __div), \
	LUNAR_METHOD(type, __unm), \
	LUNAR_METHOD(type, __len), \
	LUNAR_METHOD(type, __tostring), \
	LUNAR_METHOD(type, add), \
	LUNAR_METHOD(type, sub), \
	LUNAR_METHOD(type, mul), \
	LUNAR_METHOD(type, div), \
	LUNAR_METHOD(type, set), \
	LUNAR_METHOD(type, rows), \
	LUNAR_METHOD(type, cols), \
	LUNAR_METHOD(type, size), \
	LUNAR_METHOD(type, data), \
	LUNAR_METHOD(type, setZero), \
	LUNAR_METHOD(type, totable)

#define MATRIX_METHODS(type) \
	MATRIXBASE_METHODS(type), \
	LUNAR_METHOD(type, determinant), \
	LUNAR_METHOD(type, inverse), \
	LUNAR_METHOD(type, transpose)

#define VECTOR_METHODS(type) \
	MATRIXBASE_METHODS(type), \
	LUNAR_METHOD(type, dot), \
	LUNAR_METHOD(type, norm), \
	LUNAR_METHOD(type, squaredNorm)


namespace LuaEigen {
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
	int VectorXf::onpush(lua_State *L) {
		Lunar<Type>::extend(L);                                     // [-0,+0,e]
		Lunar<Segment<Type, 2, 1>>::push(L, new Segment<Type, 2, 1>(this), true); // [-0,+1,e]
		lua_setfield(L, -2, "segment2");                            // [-1,+0,e]
		Lunar<Segment<Type, 3, 1>>::push(L, new Segment<Type, 3, 1>(this), true); // [-0,+1,e]
		lua_setfield(L, -2, "segment3");                            // [-1,+0,e]
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
	int VectorXf::oninit(lua_State *L) {
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
	const char Vector2Tf::className[] = "Vector2Tf";
	template<>
	const LunarType<Vector2Tf>::Reg Vector2Tf::methods[] = {
		VECTOR_METHODS(Vector2Tf),
		LUNAR_METHOD(Vector2Tf, x),
		LUNAR_METHOD(Vector2Tf, y),
		{NULL, NULL}
	};

	template<>
	const char Vector3Tf::className[] = "Vector3Tf";
	template<>
	const LunarType<Vector3Tf>::Reg Vector3Tf::methods[] = {
		VECTOR_METHODS(Vector3Tf),
		LUNAR_METHOD(Vector3Tf, x),
		LUNAR_METHOD(Vector3Tf, y),
		LUNAR_METHOD(Vector3Tf, z),
		LUNAR_METHOD(Vector3Tf, cross),
		{NULL, NULL}
	};

	template<>
	const char Vector4Tf::className[] = "Vector4Tf";
	template<>
	const LunarType<Vector4Tf>::Reg Vector4Tf::methods[] = {
		VECTOR_METHODS(Vector4Tf),
		LUNAR_METHOD(Vector4Tf, x),
		LUNAR_METHOD(Vector4Tf, y),
		LUNAR_METHOD(Vector4Tf, z),
		LUNAR_METHOD(Vector4Tf, w),
		{NULL, NULL}
	};

	template<>
	int VectorXTf::onpush(lua_State *L) {
		Lunar<Type>::extend(L);                                     // [-0,+0,e]
		Lunar<Segment<Type, 1, 2>>::push(L, new Segment<Type, 1, 2>(this), true); // [-0,+1,e]
		lua_setfield(L, -2, "segment2");                            // [-1,+0,e]
		Lunar<Segment<Type, 1, 3>>::push(L, new Segment<Type, 1, 3>(this), true); // [-0,+1,e]
		lua_setfield(L, -2, "segment3");                            // [-1,+0,e]
		return 0;
	}
	template<>
	int VectorXTf::resize(lua_State *L) {
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
	int VectorXTf::oninit(lua_State *L) {
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
	const char VectorXTf::className[] = "VectorXTf";
	template<>
	const LunarType<VectorXTf>::Reg VectorXTf::methods[] = {
		VECTOR_METHODS(VectorXTf),
		LUNAR_METHOD(VectorXTf, resize),
		{NULL, NULL}
	};

	template<>
	const char SegmentXTf2::className[] = "SegmentXTf2";
	template<>
	const LunarType<SegmentXTf2>::Reg SegmentXTf2::methods[] = {
		SEGMENT_METHODS(SegmentXTf2),
		{NULL, NULL}
	};

	template<>
	const char SegmentXTf3::className[] = "SegmentXTf3";
	template<>
	const LunarType<SegmentXTf3>::Reg SegmentXTf3::methods[] = {
		SEGMENT_METHODS(SegmentXTf3),
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
	int MatrixXf::oninit(lua_State *L) {
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
	int Matrix2Xf::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(Eigen::NoChange, n);
		setZero();
		return 0;
	}
	template<>
	int Matrix2Xf::oninit(lua_State *L) {
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
	const char Matrix2Xf::className[] = "Matrix2Xf";
	template<>
	const LunarType<Matrix2Xf>::Reg Matrix2Xf::methods[] = {
		MATRIX_METHODS(Matrix2Xf),
		LUNAR_METHOD(Matrix2Xf, resize),
		{NULL, NULL}
	};

	template<>
	int Matrix3Xf::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(Eigen::NoChange, n);
		setZero();
		return 0;
	}
	template<>
	int Matrix3Xf::oninit(lua_State *L) {
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
	const char Matrix3Xf::className[] = "Matrix3Xf";
	template<>
	const LunarType<Matrix3Xf>::Reg Matrix3Xf::methods[] = {
		MATRIX_METHODS(Matrix3Xf),
		LUNAR_METHOD(Matrix3Xf, resize),
		{NULL, NULL}
	};

	template<>
	int Matrix4Xf::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(Eigen::NoChange, n);
		setZero();
		return 0;
	}
	template<>
	int Matrix4Xf::oninit(lua_State *L) {
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
	const char Matrix4Xf::className[] = "Matrix4Xf";
	template<>
	const LunarType<Matrix4Xf>::Reg Matrix4Xf::methods[] = {
		MATRIX_METHODS(Matrix4Xf),
		LUNAR_METHOD(Matrix4Xf, resize),
		{NULL, NULL}
	};

	template<>
	int MatrixX2f::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(n, Eigen::NoChange);
		setZero();
		return 0;
	}
	template<>
	int MatrixX2f::oninit(lua_State *L) {
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
	const char MatrixX2f::className[] = "MatrixX2f";
	template<>
	const LunarType<MatrixX2f>::Reg MatrixX2f::methods[] = {
		MATRIX_METHODS(MatrixX2f),
		LUNAR_METHOD(MatrixX2f, resize),
		{NULL, NULL}
	};

	template<>
	int MatrixX3f::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(n, Eigen::NoChange);
		setZero();
		return 0;
	}
	template<>
	int MatrixX3f::oninit(lua_State *L) {
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
	const char MatrixX3f::className[] = "MatrixX3f";
	template<>
	const LunarType<MatrixX3f>::Reg MatrixX3f::methods[] = {
		MATRIX_METHODS(MatrixX3f),
		LUNAR_METHOD(MatrixX3f, resize),
		{NULL, NULL}
	};

	template<>
	int MatrixX4f::resize(lua_State *L) {
		int isnum = false;
		float n = lua_tonumberx(L, 2, &isnum);
		if (!isnum) {
			return luaL_argerror(L, 2, "Argument must be a number");
		}
		resize(n, Eigen::NoChange);
		setZero();
		return 0;
	}
	template<>
	int MatrixX4f::oninit(lua_State *L) {
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
	const char MatrixX4f::className[] = "MatrixX4f";
	template<>
	const LunarType<MatrixX4f>::Reg MatrixX4f::methods[] = {
		MATRIX_METHODS(MatrixX4f),
		LUNAR_METHOD(MatrixX4f, resize),
		{NULL, NULL}
	};

	template<>
	const char Matrix32f::className[] = "Matrix32f";
	template<>
	const LunarType<Matrix32f>::Reg Matrix32f::methods[] = {
		MATRIX_METHODS(Matrix32f),
		{NULL, NULL}
	};

	template<>
	const char Matrix23f::className[] = "Matrix23f";
	template<>
	const LunarType<Matrix23f>::Reg Matrix23f::methods[] = {
		MATRIX_METHODS(Matrix23f),
		{NULL, NULL}
	};

	template<>
	const char Matrix24f::className[] = "Matrix24f";
	template<>
	const LunarType<Matrix24f>::Reg Matrix24f::methods[] = {
		MATRIX_METHODS(Matrix24f),
		{NULL, NULL}
	};

	template<>
	const char Matrix34f::className[] = "Matrix34f";
	template<>
	const LunarType<Matrix34f>::Reg Matrix34f::methods[] = {
		MATRIX_METHODS(Matrix34f),
		{NULL, NULL}
	};

	template<>
	const char Matrix42f::className[] = "Matrix42f";
	template<>
	const LunarType<Matrix42f>::Reg Matrix42f::methods[] = {
		MATRIX_METHODS(Matrix42f),
		{NULL, NULL}
	};

	template<>
	const char Matrix43f::className[] = "Matrix43f";
	template<>
	const LunarType<Matrix43f>::Reg Matrix43f::methods[] = {
		MATRIX_METHODS(Matrix43f),
		{NULL, NULL}
	};
}
