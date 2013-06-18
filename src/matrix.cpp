#include "matrix.hpp"

namespace LuaEigen {
	template<>
	const char Matrix1f::className[] = "Matrix1f";
	template<>
	const LunarType<Matrix1f>::Reg Matrix1f::methods[] = {
		LUNAR_METHOD(Matrix1f, __add),
		LUNAR_METHOD(Matrix1f, __sub),
		LUNAR_METHOD(Matrix1f, __mul),
		LUNAR_METHOD(Matrix1f, __unm),
		LUNAR_METHOD(Matrix1f, __tostring),
		LUNAR_METHOD(Matrix1f, data),
		LUNAR_METHOD(Matrix1f, setZero),
		LUNAR_METHOD(Matrix1f, inverse),
		LUNAR_METHOD(Matrix1f, transpose),
		{NULL, NULL}
	};
	template<>
	const char Matrix2f::className[] = "Matrix2f";
	template<>
	const LunarType<Matrix2f>::Reg Matrix2f::methods[] = {
		LUNAR_METHOD(Matrix2f, __add),
		LUNAR_METHOD(Matrix2f, __sub),
		LUNAR_METHOD(Matrix2f, __mul),
		LUNAR_METHOD(Matrix2f, __unm),
		LUNAR_METHOD(Matrix2f, __tostring),
		LUNAR_METHOD(Matrix2f, data),
		LUNAR_METHOD(Matrix2f, setZero),
		LUNAR_METHOD(Matrix2f, inverse),
		LUNAR_METHOD(Matrix2f, transpose),
		{NULL, NULL}
	};
	template<>
	const char Matrix3f::className[] = "Matrix3f";
	template<>
	const LunarType<Matrix3f>::Reg Matrix3f::methods[] = {
		LUNAR_METHOD(Matrix3f, __add),
		LUNAR_METHOD(Matrix3f, __sub),
		LUNAR_METHOD(Matrix3f, __mul),
		LUNAR_METHOD(Matrix3f, __unm),
		LUNAR_METHOD(Matrix3f, __tostring),
		LUNAR_METHOD(Matrix3f, data),
		LUNAR_METHOD(Matrix3f, setZero),
		LUNAR_METHOD(Matrix3f, inverse),
		LUNAR_METHOD(Matrix3f, transpose),
		{NULL, NULL}
	};
	template<>
	const char Matrix4f::className[] = "Matrix4f";
	template<>
	const LunarType<Matrix4f>::Reg Matrix4f::methods[] = {
		LUNAR_METHOD(Matrix4f, __add),
		LUNAR_METHOD(Matrix4f, __sub),
		LUNAR_METHOD(Matrix4f, __mul),
		LUNAR_METHOD(Matrix4f, __unm),
		LUNAR_METHOD(Matrix4f, __tostring),
		LUNAR_METHOD(Matrix4f, data),
		LUNAR_METHOD(Matrix4f, setZero),
		LUNAR_METHOD(Matrix4f, inverse),
		LUNAR_METHOD(Matrix4f, transpose),
		{NULL, NULL}
	};
	template<>
	const char MatrixXf::className[] = "MatrixXf";
	template<>
	const LunarType<MatrixXf>::Reg MatrixXf::methods[] = {
		LUNAR_METHOD(MatrixXf, __add),
		LUNAR_METHOD(MatrixXf, __sub),
		LUNAR_METHOD(MatrixXf, __mul),
		LUNAR_METHOD(MatrixXf, __unm),
		LUNAR_METHOD(MatrixXf, __tostring),
		LUNAR_METHOD(MatrixXf, data),
		LUNAR_METHOD(MatrixXf, setZero),
		LUNAR_METHOD(MatrixXf, inverse),
		LUNAR_METHOD(MatrixXf, transpose),
		{NULL, NULL}
	};
	template<>
	const char Vector2f::className[] = "Vector2f";
	template<>
	const LunarType<Vector2f>::Reg Vector2f::methods[] = {
		LUNAR_METHOD(Vector2f, __add),
		LUNAR_METHOD(Vector2f, __sub),
		LUNAR_METHOD(Vector2f, __mul),
		LUNAR_METHOD(Vector2f, __div),
		LUNAR_METHOD(Vector2f, __unm),
		LUNAR_METHOD(Vector2f, __tostring),
		LUNAR_METHOD(Vector2f, x),
		LUNAR_METHOD(Vector2f, y),
		LUNAR_METHOD(Vector2f, data),
		LUNAR_METHOD(Vector2f, setZero),
		LUNAR_METHOD(Vector2f, dot),
		LUNAR_METHOD(Vector2f, norm),
		LUNAR_METHOD(Vector2f, squaredNorm),
		{NULL, NULL}
	};
	template<>
	const char Vector3f::className[] = "Vector3f";
	template<>
	const LunarType<Vector3f>::Reg Vector3f::methods[] = {
		LUNAR_METHOD(Vector3f, __add),
		LUNAR_METHOD(Vector3f, __sub),
		LUNAR_METHOD(Vector3f, __mul),
		LUNAR_METHOD(Vector3f, __div),
		LUNAR_METHOD(Vector3f, __unm),
		LUNAR_METHOD(Vector3f, __tostring),
		LUNAR_METHOD(Vector3f, x),
		LUNAR_METHOD(Vector3f, y),
		LUNAR_METHOD(Vector3f, z),
		LUNAR_METHOD(Vector3f, data),
		LUNAR_METHOD(Vector3f, setZero),
		LUNAR_METHOD(Vector3f, dot),
		LUNAR_METHOD(Vector3f, cross),
		LUNAR_METHOD(Vector3f, norm),
		LUNAR_METHOD(Vector3f, squaredNorm),
		{NULL, NULL}
	};
	template<>
	const char Vector4f::className[] = "Vector4f";
	template<>
	const LunarType<Vector4f>::Reg Vector4f::methods[] = {
		LUNAR_METHOD(Vector4f, __add),
		LUNAR_METHOD(Vector4f, __sub),
		LUNAR_METHOD(Vector4f, __mul),
		LUNAR_METHOD(Vector4f, __div),
		LUNAR_METHOD(Vector4f, __unm),
		LUNAR_METHOD(Vector4f, __tostring),
		LUNAR_METHOD(Vector4f, x),
		LUNAR_METHOD(Vector4f, y),
		LUNAR_METHOD(Vector4f, z),
		LUNAR_METHOD(Vector4f, w),
		LUNAR_METHOD(Vector4f, data),
		LUNAR_METHOD(Vector4f, setZero),
		LUNAR_METHOD(Vector4f, dot),
		LUNAR_METHOD(Vector4f, norm),
		LUNAR_METHOD(Vector4f, squaredNorm),
		{NULL, NULL}
	};
	template<>
	const char VectorXf::className[] = "VectorXf";
	template<>
	const LunarType<VectorXf>::Reg VectorXf::methods[] = {
		LUNAR_METHOD(VectorXf, __add),
		LUNAR_METHOD(VectorXf, __sub),
		LUNAR_METHOD(VectorXf, __mul),
		LUNAR_METHOD(VectorXf, __div),
		LUNAR_METHOD(VectorXf, __unm),
		LUNAR_METHOD(VectorXf, __tostring),
		LUNAR_METHOD(VectorXf, x),
		LUNAR_METHOD(VectorXf, y),
		LUNAR_METHOD(VectorXf, z),
		LUNAR_METHOD(VectorXf, w),
		LUNAR_METHOD(VectorXf, data),
		LUNAR_METHOD(VectorXf, setZero),
		LUNAR_METHOD(VectorXf, dot),
		LUNAR_METHOD(VectorXf, norm),
		LUNAR_METHOD(VectorXf, squaredNorm),
		{NULL, NULL}
	};
}
