#include "matrix.hpp"

#define MATRIXBASE_METHODS(type) \
	LUNAR_METHOD(type, __add), \
	LUNAR_METHOD(type, __sub), \
	LUNAR_METHOD(type, __mul), \
	LUNAR_METHOD(type, __div), \
	LUNAR_METHOD(type, __unm), \
	LUNAR_METHOD(type, __tostring), \
	LUNAR_METHOD(type, data), \
	LUNAR_METHOD(type, setZero)

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
	const char MatrixXf::className[] = "MatrixXf";
	template<>
	const LunarType<MatrixXf>::Reg MatrixXf::methods[] = {
		MATRIX_METHODS(MatrixXf),
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
	const char VectorXf::className[] = "VectorXf";
	template<>
	const LunarType<VectorXf>::Reg VectorXf::methods[] = {
		VECTOR_METHODS(VectorXf),
		{NULL, NULL}
	};
}
