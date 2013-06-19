#ifndef LUAEIGEN_MATRIX_HPP
#define LUAEIGEN_MATRIX_HPP

#include <Eigen/Core>
#include <Eigen/Dense>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>


namespace LuaEigen {
	template<typename _Scalar, int _Rows, int _Cols>
	class Matrix : public Eigen::Matrix<_Scalar, _Rows, _Cols> {
		typedef Matrix<_Scalar, _Rows, _Cols> Type;
		typedef Eigen::Matrix<_Scalar, _Rows, _Cols> Base;

	public:
		using typename Base::Scalar;
		using Base::RowsAtCompileTime;
		using Base::ColsAtCompileTime;

		using Base::size;
		using Base::rows;
		using Base::cols;
		using Base::x;
		using Base::y;
		using Base::z;
		using Base::w;
		using Base::data;
		using Base::setZero;
		using Base::norm;
		using Base::squaredNorm;
		using Base::inverse;
		using Base::transpose;
		using Base::dot;
		using Base::cross;

		Matrix(lua_State *L) {}
		Matrix(const Base &o) : Base(o) {}
		~Matrix() {}

		int init(lua_State *L) {
			int l_nargs = lua_gettop(L);

			if (l_nargs == 1) {
				setZero();
			}
			if (l_nargs-1 == size()) {
				for (int i = 2; i <= l_nargs; i++) {
					int isnum = false;
					float n = lua_tonumberx(L, i, &isnum);
					if (!isnum) {
						return luaL_argerror(L, i, "Argument must be a number");
					}
					(*this)((i-2)/cols(),(i-2)%cols()) = n;
				}
			}

			return 0;
		}

		int __add(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 1);
			Type *op2 = Lunar<Type>::check(L, 2);
			Lunar<Type>::push(L, new Type((*op1) + (*op2)), true);
			return 1;
		}

		int __sub(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 1);
			Type *op2 = Lunar<Type>::check(L, 2);
			Lunar<Type>::push(L, new Type((*op1) - (*op2)), true);
			return 1;
		}

		int __mul(lua_State *L) {
			Type *op1 = Lunar<Type>::test(L, 1);
			if (op1 == this) {
				int isnum = false;
				float op2s = lua_tonumberx(L, 2, &isnum);
				if (isnum) {
					Lunar<Type>::push(L, new Type((*op1) * op2s), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, 1> Op2VectorType;
				Op2VectorType *op2v = Lunar<Op2VectorType>::test(L, 2);
				if (op2v != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, 1> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2v)), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, ColsAtCompileTime> Op2QuadraticMatrixType;
				Op2QuadraticMatrixType *op2mq = Lunar<Op2QuadraticMatrixType>::test(L, 2);
				if (op2mq != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mq)), true);
					return 1;
				}

				const char *msg = lua_pushfstring(L, "Argument must be compatible with '%s'", Type::className);
				return luaL_argerror(L, 2, msg);
			}

			Type *op2 = Lunar<Type>::test(L, 2);
			if (op2 == this) {
				int isnum = false;
				float op1s = lua_tonumberx(L, 1, &isnum);
				if (isnum) {
					Lunar<Type>::push(L, new Type(op1s * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, RowsAtCompileTime, RowsAtCompileTime> Op1QuadraticMatrixType;
				Op1QuadraticMatrixType *op1mq = Lunar<Op1QuadraticMatrixType>::test(L, 1);
				if (op1mq != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1mq) * (*op2)), true);
					return 1;
				}

				const char *msg = lua_pushfstring(L, "Argument must be compatible with '%s'", Type::className);
				return luaL_argerror(L, 1, msg);
			}

			return luaL_error(L, "Expected one argument to be of type '%s'", Type::className);
		}

		int __div(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 1);
			float op2s = luaL_checknumber(L, 2);
			Lunar<Type>::push(L, new Type((*op1) / op2s), true);
			return 1;
		}

		int __unm(lua_State *L) {
			Lunar<Type>::push(L, new Type(-(*this)), true);
			return 1;
		}

		int __tostring(lua_State *L) {
			/* Write vectors more nicely */
			if (ColsAtCompileTime == 1) {
				lua_pushfstring(L, "(%f", (*this)(0,0));
				for (int i = 1; i < rows(); i++) {
					lua_pushfstring(L, ", %f", (*this)(i,0));
				}
				lua_pushliteral(L, ")");
				lua_concat(L, size()+1);
				return 1;
			}

			for (int i = 0; i < rows(); i++) {
				lua_pushfstring(L, "%f", (*this)(i,0));
				for (int j = 1; j < cols(); j++) {
					lua_pushfstring(L, ", %f", (*this)(i,j));
				}
				lua_pushliteral(L, "\n");
			}
			lua_concat(L, size()+rows());
			return 1;
		}

#define NAMED_COORD(name) \
		int name(lua_State *L) { \
			int nargs = lua_gettop(L); \
			if (nargs > 1) { \
				name() = luaL_checknumber(L, 2); \
				return 0; \
			} \
			lua_pushnumber(L, name()); \
			return 1; \
		}
		NAMED_COORD(x)
		NAMED_COORD(y)
		NAMED_COORD(z)
		NAMED_COORD(w)
#undef NAMED_COORD

		int rows(lua_State *L) {
			lua_pushinteger(L, rows());
			return 1;
		}

		int cols(lua_State *L) {
			lua_pushinteger(L, cols());
			return 1;
		}

		int size(lua_State *L) {
			lua_pushinteger(L, size());
			return 1;
		}

		int data(lua_State *L) {
			lua_pushlightuserdata(L, data());
			return 1;
		}

		int setZero(lua_State *L) {
			setZero();
			return 0;
		}

		int norm(lua_State *L) {
			lua_pushnumber(L, norm());
			return 1;
		}

		int squaredNorm(lua_State *L) {
			lua_pushnumber(L, squaredNorm());
			return 1;
		}

		int inverse(lua_State *L) {
			Lunar<Type>::push(L, new Type(inverse()), true);
			return 1;
		}

		int transpose(lua_State *L) {
			Lunar<Type>::push(L, new Type(transpose()), true);
			return 1;
		}

		int dot(lua_State *L) {
			Type *o = Lunar<Type>::check(L, 2);
			lua_pushnumber(L, dot(*o));
			return 1;
		}

		int cross(lua_State *L) {
			Type *o = Lunar<Type>::check(L, 2);
			Lunar<Type>::push(L, new Type(cross(*o)), true);
			return 1;
		}

		int segment3(lua_State *L) {
			int base_row = luaL_checkinteger(L, 2);
			Lunar<Matrix<Scalar, 3, 1>>::push(L, new Matrix<Scalar, 3, 1>(Base::template segment<3>(base_row)), true);
			return 1;
		}

		LUNAR_DECLARE(Type);
	};

	typedef Matrix<float, 2, 1> Vector2f;
	typedef Matrix<float, 3, 1> Vector3f;
	typedef Matrix<float, 4, 1> Vector4f;
	typedef Matrix<float, Eigen::Dynamic, 1> VectorXf;
	typedef Matrix<float, 1, 1> Matrix1f;
	typedef Matrix<float, 2, 2> Matrix2f;
	typedef Matrix<float, 3, 3> Matrix3f;
	typedef Matrix<float, 4, 4> Matrix4f;
	typedef Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
}

#endif
