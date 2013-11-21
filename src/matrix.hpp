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

	template<typename _VectorType, int _Size>
	class Segment {
		typedef Segment<_VectorType, _Size> Type;
		typedef Matrix<typename _VectorType::Scalar, _Size, 1> SegmentType;

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
				float table[_Size];
				if (SegmentType::fromtable(L, 3, table) == 0) {
					return luaL_argerror(L, 3, "Argument must be a VectorNf or a table of N numbers");
				}
				_vector->template segment<_Size>(base_row-1) = Eigen::Map<typename SegmentType::Base>(table);
			}
			else {
				SegmentType *value = Lunar<SegmentType>::test(L, 3);
				if (value == nullptr) {
					return luaL_argerror(L, 3, "Argument must be a VectorNf or a table of N numbers");
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
		friend class Segment<Matrix<_Scalar, Eigen::Dynamic, 1>, 2>;
		friend class Segment<Matrix<_Scalar, Eigen::Dynamic, 1>, 3>;

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

		int prep(lua_State *L) { return 0; }

		int init(lua_State *L) {
			int l_nargs = lua_gettop(L);

			if (l_nargs == 1) {
				setZero();
			}
			else if (l_nargs == 2) {
				if (iscompat(L, 2)) {
					float table[RowsAtCompileTime*ColsAtCompileTime];
					if (fromtable(L, 2, table) == 0) {
						return luaL_argerror(L, 2, "Argument must be a table of N numbers");
					}
					*this = Eigen::Map<Base>(table);
				}
				else {
					Type *o = Lunar<Type>::test(L, 2);
					if (o == nullptr) {
						return luaL_argerror(L, 2, "Argument must be a vector");
					}
					*this = *o;
				}
			}
			else if (l_nargs-1 == cols()) {
				for (int i = 2; i <= l_nargs; i++) {
					Matrix<Scalar,RowsAtCompileTime,1> *o = Lunar<Matrix<Scalar,RowsAtCompileTime,1>>::test(L, i);
					if (o == nullptr) {
						return luaL_argerror(L, i, "Argument must be a vector");
					}
					int col = i-2;
					this->template block<RowsAtCompileTime,1>(0,col) = *o;
				}
			}
			else if (l_nargs-1 == size()) {
				for (int i = 2; i <= l_nargs; i++) {
					int isnum = false;
					float n = lua_tonumberx(L, i, &isnum);
					if (!isnum) {
						return luaL_argerror(L, i, "Argument must be a number");
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

		int __len(lua_State *L) {
			lua_pushinteger(L, size());
			return 1;
		}

		int __index(lua_State *L) {
			int isint = false;
			int i = lua_tointegerx(L, 2, &isint);
			if (isint) {
				if (i < 1 || i > rows()) {
					luaL_argerror(L, 2, "Index needs to be >= 1 and <= rows()");
				}
				lua_pushnumber(L, (*this)(i-1,0)); // FIXME will break for matrices!
				return 1;
			}

			const char *identifier = lua_tostring(L, 2);
			if (identifier) {
				/* FIXME: HUGE HACK!!! But we need to access the method table somehow, without triggering ourselves... */
				if (!luaL_getmetafield(L, 1, "_methodtable")) {
					return luaL_argerror(L, 1, "self should have a _methodtable");
				}
				lua_getfield(L, -1, identifier);
				return 1;
			}

			return luaL_argerror(L, 2, "Argument needs to be an integer or string");
		}

		int __newindex(lua_State *L) {
			int isint = false;
			int i = lua_tointegerx(L, 2, &isint);
			if (isint) {
				if (i < 1 || i > rows()) {
					luaL_argerror(L, 2, "Index needs to be >= 1 and <= rows()");
				}
				(*this)(i-1,0) = luaL_checknumber(L, 3); // FIXME will break for matrices!
				return 0;
			}

			if (lua_type(L, 2) == LUA_TSTRING) {
				return Lunar<Type>::newindex_T(L);
			}

			return luaL_argerror(L, 2, "Argument needs to be an integer or string");
		}

		int __call(lua_State *L) {
			int isint = false;
			int i = lua_tointegerx(L, 2, &isint);
			if (!isint) {
				return luaL_argerror(L, 2, "Argument needs to be an integer");
			}

			if (i < 1 || i > rows()) {
				luaL_argerror(L, 2, "Index needs to be >= 1 and <= rows()");
			}

			isint = false;
			int j = lua_tointegerx(L, 3, &isint);
			if (!isint) {
				return luaL_argerror(L, 3, "Argument needs to be an integer");
			}

			if (j < 1 || j > cols()) {
				luaL_argerror(L, 3, "Index needs to be >= 1 and <= cols()");
			}

			int isnum = false;
			int f = lua_tonumberx(L, 4, &isnum);
			if (isnum) {
				(*this)(i-1,j-1) = f;
				return 0;
			}

			lua_pushnumber(L, (*this)(i-1,j-1));
			return 1;
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

	typedef Segment<VectorXf, 2> SegmentXf2;
	typedef Segment<VectorXf, 3> SegmentXf3;

	template<>
	int VectorXf::prep(lua_State *L);
	template<>
	int VectorXf::init(lua_State *L);
	template<>
	int VectorXf::resize(lua_State *L);

	template<>
	int MatrixXf::init(lua_State *L);
	template<>
	int MatrixXf::resize(lua_State *L);
}

#endif
