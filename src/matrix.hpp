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
	class Matrix;

	template<typename _VectorType, int _Rows, int _Cols>
	class Segment {
		typedef Segment<_VectorType, _Rows, _Cols> Type;
		typedef Matrix<typename _VectorType::Scalar, _Rows, _Cols> SegmentType;

		static const int _Size = _Rows*_Cols;

	public:
		Segment(lua_State *L) {assert(false);}
		Segment(_VectorType *vector)
		: _vector(vector)
		{}

		int __index(lua_State *L) {
			int base_row = luaL_checkinteger(L, 2);
			Lunar<SegmentType>::push(L, new SegmentType(_vector->template segment<_Size>(base_row-1)), true);
			return 1;
		}

		int __newindex(lua_State *L) {
			int base_row = luaL_checkinteger(L, 2);
			if (SegmentType::iscompat(L, 3)) {
				typename _VectorType::Scalar table[_Size] = {0.0};
				if (SegmentType::fromtable(L, 3, table) == 0) {
					return luaX_typeerror(L, 3, NULL, "VectorNf or table of N numbers");
				}
				_vector->template segment<_Size>(base_row-1) = Eigen::Map<typename SegmentType::Base>(table);
			}
			else {
				SegmentType *value = Lunar<SegmentType>::test(L, 3);
				if (value == nullptr) {
					return luaX_typeerror(L, 3, NULL, "VectorNf or table of N numbers");
				}
				_vector->template segment<_Size>(base_row-1) = *value;
			}
			return 0;
		}

		LUNAR_DECLARE(Type);

	private:
		_VectorType *_vector;
	};

	template<typename _Scalar, int _Rows, int _Cols>
	class Matrix : public Eigen::Matrix<_Scalar, _Rows, _Cols> {
		friend class Segment<Matrix<_Scalar, Eigen::Dynamic, 1>, 2, 1>;
		friend class Segment<Matrix<_Scalar, Eigen::Dynamic, 1>, 3, 1>;
		friend class Segment<Matrix<_Scalar, 1, Eigen::Dynamic>, 1, 2>;
		friend class Segment<Matrix<_Scalar, 1, Eigen::Dynamic>, 1, 3>;

		typedef Matrix<_Scalar, _Rows, _Cols> Type;
		typedef Eigen::Matrix<_Scalar, _Rows, _Cols> Base;

	public:
		using typename Base::Scalar;
		using Base::RowsAtCompileTime;
		using Base::ColsAtCompileTime;

		using Base::resize;
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
		using Base::determinant;
		using Base::inverse;
		using Base::transpose;
		using Base::dot;
		using Base::cross;

		Matrix(lua_State *L) : Base() {}
		template<typename OtherDerived>
		Matrix(const Eigen::MatrixBase<OtherDerived> &o) : Base(o) {}
		template<typename OtherDerived>
		Matrix(const Eigen::EigenBase<OtherDerived> &o) : Base(o) {}
		template<typename OtherDerived>
		Matrix(const Eigen::ReturnByValue<OtherDerived> &o) : Base(o) {}
		~Matrix() {}

		template<typename OtherDerived>
		Matrix &operator=(const Eigen::MatrixBase<OtherDerived> &o) {
			Base::operator=(o);
			return *this;
		}

		template<typename OtherDerived>
		Matrix &operator=(const Eigen::EigenBase<OtherDerived> &o) {
			Base::operator=(o);
			return *this;
		}

		template<typename OtherDerived>
		Matrix &operator=(const Eigen::ReturnByValue<OtherDerived> &o) {
			Base::operator=(o);
			return *this;
		}

		int onpush(lua_State *L) { return 0; }

		int oninit(lua_State *L) {
			int l_nargs = lua_gettop(L);

			if (l_nargs == 1) {
				setZero();
			}
			else if (l_nargs == 2) {
				if (iscompat(L, 2)) {
					Scalar table[RowsAtCompileTime*ColsAtCompileTime] = {0.0};
					if (fromtable(L, 2, table) == 0) {
						return luaX_typeerror(L, 2, NULL, "table of N numbers");
					}
					*this = Eigen::Map<Base>(table);
				}
				else {
					Type *o = Lunar<Type>::test(L, 2);
					if (o == nullptr) {
						return luaX_typeerror(L, 2, NULL, "vector");
					}
					*this = *o;
				}
			}
			else if (l_nargs-1 == cols()) {
				for (int i = 2; i <= l_nargs; i++) {
					Matrix<Scalar,RowsAtCompileTime,1> *o = Lunar<Matrix<Scalar,RowsAtCompileTime,1>>::test(L, i);
					if (o == nullptr) {
						return luaX_typeerror(L, i, NULL, "vector");
					}
					int col = i-2;
					this->template block<RowsAtCompileTime,1>(0,col) = *o;
				}
			}
			else if (l_nargs-1 == size()) {
				for (int i = 2; i <= l_nargs; i++) {
					int isnum = false;
					Scalar n = lua_tonumberx(L, i, &isnum);
					if (!isnum) {
						return luaX_typeerror(L, i, NULL, "number");
					}
					int idx = i-2, row = idx/cols(), col = idx%cols();
					(*this)(row,col) = n;
				}
			}
			else {
				return luaL_error(L, "Unexpected number of arguments");
			}

			return 0;
		}

		static int iscompat(lua_State *L, int index) {
			return lua_istable(L, index) && lua_rawlen(L, index) == RowsAtCompileTime*ColsAtCompileTime;
		}

		static int fromtable(lua_State *L, int index, Scalar array[RowsAtCompileTime*ColsAtCompileTime]) {
			for (int i = 1; i <= RowsAtCompileTime; i++) {
				for (int j = 1; j <= ColsAtCompileTime; j++) {
					int isnum = false;
					lua_rawgeti(L, index, i*j);
					array[i-1] = lua_tonumberx(L, -1, &isnum);
					if (!isnum) {
						return 0;
					}
				}
			}

			return 1;
		}

		int totable(lua_State *L) {
			lua_createtable(L, RowsAtCompileTime*ColsAtCompileTime, 0);
			for (int i = 1; i <= RowsAtCompileTime; i++) {
				for (int j = 1; j <= ColsAtCompileTime; j++) {
					lua_pushnumber(L, (*this)(i-1, j-1));
					lua_rawseti(L, -2, i*j);
				}
			}
			return 1;
		}

		static int argerror(lua_State *L, int self, int op1, int op2) {
			const char *msg = lua_pushfstring(L, "'%s' is not a valid target for this operation: type(op1)='%s', type(op2)='%s'", luaX_typename(L, self), luaX_typename(L, op1), luaX_typename(L, op2));
			return luaL_argerror(L, self, msg);
		}

		int set(lua_State *L) {
			int isint = false;
			int i = lua_tointegerx(L, 2, &isint);
			if (isint) {
				if (ColsAtCompileTime == 1) {
					if (i < 1 || i > rows()) {
						return luaL_argerror(L, 2, "Index needs to be >= 1 and <= rows()");
					}
					(*this)(i-1,0) = luaL_checknumber(L, 3);
					return 0;
				}
				else if (RowsAtCompileTime == 1) {
					if (i < 1 || i > cols()) {
						return luaL_argerror(L, 2, "Index needs to be >= 1 and <= cols()");
					}
					(*this)(0,i-1) = luaL_checknumber(L, 3);
					return 0;
				}
				return luaL_argerror(L, 2, "Cannot index a matrix using one integer alone");
			}

			if (lua_type(L, 2) == LUA_TTABLE) {
				lua_rawgeti(L, 2, 1);
				isint = false;
				int i = lua_tointegerx(L, -1, &isint);
				if (!isint) {
					return luaX_typeerror(L, 2, NULL, "{integer, integer}");
				}
				if (i < 1 || i > rows()) {
					return luaL_argerror(L, 2, "First index needs to be >= 1 and <= rows()");
				}

				lua_rawgeti(L, 2, 2);
				isint = false;
				int j = lua_tointegerx(L, -1, &isint);
				if (!isint) {
					return luaX_typeerror(L, 2, NULL, "{integer, integer}");
				}
				if (j < 1 || j > cols()) {
					return luaL_argerror(L, 2, "Second index needs to be >= 1 and <= cols()");
				}

				(*this)(i-1,j-1) = luaL_checknumber(L, 3);
				return 0;
			}

			return luaX_typeerror(L, 2, NULL, "integer or table");
		}

		int add(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 2);
			Type *op2 = Lunar<Type>::check(L, 3);
			*this = (*op1) + (*op2);
			lua_pop(L, 2);
			return 1;
		}

		int sub(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 2);
			Type *op2 = Lunar<Type>::check(L, 3);
			*this = (*op1) - (*op2);
			lua_pop(L, 2);
			return 1;
		}

		int mul(lua_State *L) {
			const int self_idx = 1;
			const int op1_idx = 2;
			const int op2_idx = 3;

			int isnum = false;
			Scalar op1s = lua_tonumberx(L, op1_idx, &isnum);
			if (isnum) {
				int isnum = false;
				Scalar op2s = lua_tonumberx(L, op2_idx, &isnum);
				if (isnum) {
					if (RowsAtCompileTime == 1 && ColsAtCompileTime == 1) {
						(*this)(0,0) = op1s * op2s;
						lua_pop(L, 2);
						return 1;
					}

					return argerror(L, self_idx, op1_idx, op2_idx);
				}

				typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> Op2MatrixType;
				Op2MatrixType *op2m = Lunar<Op2MatrixType>::test(L, op2_idx);
				if (op2m != nullptr) {
					*this = op1s * (*op2m);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			/* Catch a matching matrix size early, because (contrary to all other operations) it allows multiplication with a scalar */
			typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> Op1MatrixType;
			Op1MatrixType *op1m = Lunar<Op1MatrixType>::test(L, op1_idx);
			if (op1m != nullptr) {
				int isnum = false;
				Scalar op2s = lua_tonumberx(L, op2_idx, &isnum);
				if (isnum) {
					*this = (*op1m) * op2s;
					lua_pop(L, 2);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, ColsAtCompileTime> Op2MatrixType;
				Op2MatrixType *op2m = Lunar<Op2MatrixType>::test(L, op2_idx);
				if (op2m != nullptr) {
					*this = (*op1m) * (*op2m);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			typedef Matrix<Scalar, RowsAtCompileTime, 1> Op1MatrixN1Type;
			Op1MatrixN1Type *op1mN1 = Lunar<Op1MatrixN1Type>::test(L, op1_idx);
			if (op1mN1 != nullptr) {
				typedef Matrix<Scalar, 1, ColsAtCompileTime> Op2Matrix1NType;
				Op2Matrix1NType *op2m1N = Lunar<Op2Matrix1NType>::test(L, op2_idx);
				if (op2m1N != nullptr) {
					*this = (*op1mN1) * (*op2m1N);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			typedef Matrix<Scalar, RowsAtCompileTime, 2> Op1MatrixN2Type;
			Op1MatrixN2Type *op1mN2 = Lunar<Op1MatrixN2Type>::test(L, op1_idx);
			if (op1mN2 != nullptr) {
				typedef Matrix<Scalar, 2, ColsAtCompileTime> Op2Matrix2NType;
				Op2Matrix2NType *op2m2N = Lunar<Op2Matrix2NType>::test(L, op2_idx);
				if (op2m2N != nullptr) {
					*this = (*op1mN2) * (*op2m2N);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			typedef Matrix<Scalar, RowsAtCompileTime, 3> Op1MatrixN3Type;
			Op1MatrixN3Type *op1mN3 = Lunar<Op1MatrixN3Type>::test(L, op1_idx);
			if (op1mN3 != nullptr) {
				typedef Matrix<Scalar, 3, ColsAtCompileTime> Op2Matrix3NType;
				Op2Matrix3NType *op2m3N = Lunar<Op2Matrix3NType>::test(L, op2_idx);
				if (op2m3N != nullptr) {
					*this = (*op1mN3) * (*op2m3N);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			typedef Matrix<Scalar, RowsAtCompileTime, 4> Op1MatrixN4Type;
			Op1MatrixN4Type *op1mN4 = Lunar<Op1MatrixN4Type>::test(L, op1_idx);
			if (op1mN4 != nullptr) {
				typedef Matrix<Scalar, 4, ColsAtCompileTime> Op2Matrix4NType;
				Op2Matrix4NType *op2m4N = Lunar<Op2Matrix4NType>::test(L, op2_idx);
				if (op2m4N != nullptr) {
					*this = (*op1mN4) * (*op2m4N);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			typedef Matrix<Scalar, RowsAtCompileTime, Eigen::Dynamic> Op1MatrixNXType;
			Op1MatrixNXType *op1NX = Lunar<Op1MatrixNXType>::test(L, op1_idx);
			if (op1NX != nullptr) {
				typedef Matrix<Scalar, Eigen::Dynamic, ColsAtCompileTime> Op2MatrixXNType;
				Op2MatrixXNType *op2mXN = Lunar<Op2MatrixXNType>::test(L, op2_idx);
				if (op2mXN != nullptr) {
					*this = (*op1NX) * (*op2mXN);
					lua_pop(L, 2);
					return 1;
				}

				return argerror(L, self_idx, op1_idx, op2_idx);
			}

			return argerror(L, self_idx, op1_idx, op2_idx);
		}

		int div(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 2);
			Scalar op2s = luaL_checknumber(L, 3);
			*this = (*op1) / op2s;
			lua_pop(L, 2);
			return 1;
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
				Scalar op2s = lua_tonumberx(L, 2, &isnum);
				if (isnum) {
					Lunar<Type>::push(L, new Type((*op1) * op2s), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, 1> Op2MatrixN1Type;
				Op2MatrixN1Type *op2mN1 = Lunar<Op2MatrixN1Type>::test(L, 2);
				if (op2mN1 != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, 1> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mN1)), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, 2> Op2MatrixN2Type;
				Op2MatrixN2Type *op2mN2 = Lunar<Op2MatrixN2Type>::test(L, 2);
				if (op2mN2 != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, 2> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mN2)), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, 3> Op2MatrixN3Type;
				Op2MatrixN3Type *op2mN3 = Lunar<Op2MatrixN3Type>::test(L, 2);
				if (op2mN3 != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, 3> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mN3)), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, 4> Op2MatrixN4Type;
				Op2MatrixN4Type *op2mN4 = Lunar<Op2MatrixN4Type>::test(L, 2);
				if (op2mN4 != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, 4> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mN4)), true);
					return 1;
				}

				typedef Matrix<Scalar, ColsAtCompileTime, Eigen::Dynamic> Op2MatrixNXType;
				Op2MatrixNXType *op2mNX = Lunar<Op2MatrixNXType>::test(L, 2);
				if (op2mNX != nullptr) {
					typedef Matrix<Scalar, RowsAtCompileTime, Eigen::Dynamic> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1) * (*op2mNX)), true);
					return 1;
				}

				const char *msg = lua_pushfstring(L, "Argument must be compatible with '%s'", Type::className);
				return luaL_argerror(L, 2, msg);
			}

			Type *op2 = Lunar<Type>::test(L, 2);
			if (op2 == this) {
				int isnum = false;
				Scalar op1s = lua_tonumberx(L, 1, &isnum);
				if (isnum) {
					Lunar<Type>::push(L, new Type(op1s * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, 1, RowsAtCompileTime> Op1Matrix1NType;
				Op1Matrix1NType *op1m1N = Lunar<Op1Matrix1NType>::test(L, 2);
				if (op1m1N != nullptr) {
					typedef Matrix<Scalar, 1, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1m1N) * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, 2, RowsAtCompileTime> Op1Matrix2NType;
				Op1Matrix2NType *op1m2N = Lunar<Op1Matrix2NType>::test(L, 2);
				if (op1m2N != nullptr) {
					typedef Matrix<Scalar, 2, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1m2N) * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, 3, RowsAtCompileTime> Op1Matrix3NType;
				Op1Matrix3NType *op1m3N = Lunar<Op1Matrix3NType>::test(L, 2);
				if (op1m3N != nullptr) {
					typedef Matrix<Scalar, 3, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1m3N) * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, 4, RowsAtCompileTime> Op1Matrix4NType;
				Op1Matrix4NType *op1m4N = Lunar<Op1Matrix4NType>::test(L, 2);
				if (op1m4N != nullptr) {
					typedef Matrix<Scalar, 4, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1m4N) * (*op2)), true);
					return 1;
				}

				typedef Matrix<Scalar, Eigen::Dynamic, RowsAtCompileTime> Op1MatrixXNType;
				Op1MatrixXNType *op1mXN = Lunar<Op1MatrixXNType>::test(L, 2);
				if (op1mXN != nullptr) {
					typedef Matrix<Scalar, Eigen::Dynamic, ColsAtCompileTime> ResultType;
					Lunar<ResultType>::push(L, new ResultType((*op1mXN) * (*op2)), true);
					return 1;
				}

				const char *msg = lua_pushfstring(L, "Argument must be compatible with '%s'", Type::className);
				return luaL_argerror(L, 1, msg);
			}

			return luaL_error(L, "Expected one argument to be of type '%s'", Type::className);
		}

		int __div(lua_State *L) {
			Type *op1 = Lunar<Type>::check(L, 1);
			Scalar op2s = luaL_checknumber(L, 2);
			Lunar<Type>::push(L, new Type((*op1) / op2s), true);
			return 1;
		}

		int __unm(lua_State *L) {
			Lunar<Type>::push(L, new Type(-(*this)), true);
			return 1;
		}

		int __len(lua_State *L) {
			lua_pushinteger(L, size());
			return 1;
		}

		int __call(lua_State *L) {
			int isint = false;
			int i = lua_tointegerx(L, 2, &isint);
			if (isint) {
				if (ColsAtCompileTime == 1) {
					if (i < 1 || i > rows()) {
						return luaL_argerror(L, 2, "Index needs to be >= 1 and <= rows()");
					}
					lua_pushnumber(L, (*this)(i-1,0));
					return 1;
				}
				else if (RowsAtCompileTime == 1) {
					if (i < 1 || i > cols()) {
						return luaL_argerror(L, 2, "Index needs to be >= 1 and <= cols()");
					}
					lua_pushnumber(L, (*this)(0,i-1));
					return 1;
				}
				return luaL_argerror(L, 2, "Cannot index a matrix using one integer alone");
			}

			if (lua_type(L, 2) == LUA_TTABLE) {
				lua_rawgeti(L, 2, 1);
				isint = false;
				int i = lua_tointegerx(L, -1, &isint);
				if (!isint) {
					return luaX_typeerror(L, 2, NULL, "{integer, integer}");
				}
				if (i < 1 || i > rows()) {
					return luaL_argerror(L, 2, "First index needs to be >= 1 and <= rows()");
				}

				lua_rawgeti(L, 2, 2);
				isint = false;
				int j = lua_tointegerx(L, -1, &isint);
				if (!isint) {
					return luaX_typeerror(L, 2, NULL, "{integer, integer}");
				}
				if (j < 1 || j > cols()) {
					return luaL_argerror(L, 2, "Second index needs to be >= 1 and <= cols()");
				}

				lua_pushnumber(L, (*this)(i-1,j-1));
				return 1;
			}

			return luaX_typeerror(L, 2, NULL, "integer or table");
		}

		int __tostring(lua_State *L) {
			/* Write vectors more nicely */
			if (ColsAtCompileTime == 1) {
				lua_pushliteral(L, "(");
				if (rows() > 0) {
					lua_pushfstring(L, "%f", (*this)(0,0));
				}
				for (int i = 1; i < rows(); i++) {
					lua_pushfstring(L, ", %f", (*this)(i,0));
				}
				lua_pushliteral(L, ")");
				lua_concat(L, size()+2);
				return 1;
			}

			for (int i = 0; i < rows(); i++) {
				if (cols() > 0) {
					lua_pushfstring(L, "%f", (*this)(i,0));
				}
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

		int resize(lua_State *L);

		int size(lua_State *L) {
			lua_pushinteger(L, size());
			return 1;
		}

		int rows(lua_State *L) {
			lua_pushinteger(L, rows());
			return 1;
		}

		int cols(lua_State *L) {
			lua_pushinteger(L, cols());
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

		int determinant(lua_State *L) {
			lua_pushnumber(L, determinant());
			return 1;
		}

		int inverse(lua_State *L) {
			Lunar<Matrix<_Scalar, _Cols, _Rows>>::push(L, new Matrix<_Scalar, _Cols, _Rows>(inverse()), true);
			return 1;
		}

		int transpose(lua_State *L) {
			Lunar<Matrix<_Scalar, _Cols, _Rows>>::push(L, new Matrix<_Scalar, _Cols, _Rows>(transpose()), true);
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

		LUNAR_DECLARE(Type);
	};

	typedef Matrix<float, 2, 1> Vector2f;
	typedef Matrix<float, 3, 1> Vector3f;
	typedef Matrix<float, 4, 1> Vector4f;
	typedef Matrix<float, Eigen::Dynamic, 1> VectorXf;

	typedef Segment<VectorXf, 2, 1> SegmentXf2;
	typedef Segment<VectorXf, 3, 1> SegmentXf3;

	typedef Matrix<float, 1, 2> Vector2Tf;
	typedef Matrix<float, 1, 3> Vector3Tf;
	typedef Matrix<float, 1, 4> Vector4Tf;
	typedef Matrix<float, 1, Eigen::Dynamic> VectorXTf;

	typedef Segment<VectorXTf, 1, 2> SegmentXTf2;
	typedef Segment<VectorXTf, 1, 3> SegmentXTf3;

	typedef Matrix<float, 1, 1> Matrix1f;
	typedef Matrix<float, 2, 2> Matrix2f;
	typedef Matrix<float, 3, 3> Matrix3f;
	typedef Matrix<float, 4, 4> Matrix4f;
	typedef Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;

	typedef Matrix<float, 2, Eigen::Dynamic> Matrix2Xf;
	typedef Matrix<float, 3, Eigen::Dynamic> Matrix3Xf;
	typedef Matrix<float, 4, Eigen::Dynamic> Matrix4Xf;

	typedef Matrix<float, Eigen::Dynamic, 2> MatrixX2f;
	typedef Matrix<float, Eigen::Dynamic, 3> MatrixX3f;
	typedef Matrix<float, Eigen::Dynamic, 4> MatrixX4f;

	typedef Matrix<float, 3, 2> Matrix32f;

	typedef Matrix<float, 2, 3> Matrix23f;

	typedef Matrix<float, 2, 4> Matrix24f;
	typedef Matrix<float, 3, 4> Matrix34f;

	typedef Matrix<float, 4, 2> Matrix42f;
	typedef Matrix<float, 4, 3> Matrix43f;

	template<>
	int VectorXf::oninit(lua_State *L);
	template<>
	int VectorXf::onpush(lua_State *L);
	template<>
	int VectorXf::resize(lua_State *L);

	template<>
	int VectorXTf::onpush(lua_State *L);
	template<>
	int VectorXTf::oninit(lua_State *L);
	template<>
	int VectorXTf::resize(lua_State *L);

	template<>
	int MatrixXf::oninit(lua_State *L);
	template<>
	int MatrixXf::resize(lua_State *L);

	template<>
	int Matrix2Xf::oninit(lua_State *L);
	template<>
	int Matrix2Xf::resize(lua_State *L);

	template<>
	int Matrix3Xf::oninit(lua_State *L);
	template<>
	int Matrix3Xf::resize(lua_State *L);

	template<>
	int Matrix4Xf::oninit(lua_State *L);
	template<>
	int Matrix4Xf::resize(lua_State *L);

	template<>
	int MatrixX2f::oninit(lua_State *L);
	template<>
	int MatrixX2f::resize(lua_State *L);

	template<>
	int MatrixX3f::oninit(lua_State *L);
	template<>
	int MatrixX3f::resize(lua_State *L);

	template<>
	int MatrixX4f::oninit(lua_State *L);
	template<>
	int MatrixX4f::resize(lua_State *L);
}

#endif
