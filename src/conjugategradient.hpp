#ifndef LUAEIGEN_CONJUGATEGRADIENT_HPP
#define LUAEIGEN_CONJUGATEGRADIENT_HPP

#include <Eigen/IterativeLinearSolvers>

extern "C" {
#include <lua.h>
}

#include <lunar.hpp>

#include "matrix.hpp"


namespace LuaEigen {
  template<typename _MatrixType, int _UpLo = Eigen::Lower, typename _Preconditioner = Eigen::DiagonalPreconditioner<typename _MatrixType::Scalar>>
	class ConjugateGradient : public Eigen::ConjugateGradient<_MatrixType, _UpLo, _Preconditioner> {
    typedef ConjugateGradient<_MatrixType, _UpLo, _Preconditioner> Type;
    typedef Eigen::ConjugateGradient<_MatrixType, _UpLo, _Preconditioner> Base;

    using Base::compute;
    using Base::solve;
    using Base::solveWithGuess;

public:
		ConjugateGradient(lua_State *L) : Base() {}
		~ConjugateGradient() {}

    int compute(lua_State *L) {
			_MatrixType *A = Lunar<_MatrixType>::check(L, 2);
      this->compute(*A);
			lua_pop(L, 1);
			return 1;
		}

    int solve(lua_State *L) {
      typedef Matrix<typename _MatrixType::Scalar, _MatrixType::RowsAtCompileTime, 1> RhsType;
      typedef Matrix<typename _MatrixType::Scalar, _MatrixType::ColsAtCompileTime, 1> ResultType;

      RhsType *b = Lunar<RhsType>::check(L, 2);
      Lunar<ResultType>::push(L, new ResultType(this->solve(*b)), true);
			return 1;
    }

    int solveWithGuess(lua_State *L) {
      typedef Matrix<typename _MatrixType::Scalar, _MatrixType::RowsAtCompileTime, 1> RhsType;
      typedef Matrix<typename _MatrixType::Scalar, _MatrixType::ColsAtCompileTime, 1> ResultType;

      RhsType *b = Lunar<RhsType>::check(L, 2);
      ResultType *x0 = Lunar<ResultType>::check(L, 3);
      Lunar<ResultType>::push(L, new ResultType(this->solveWithGuess(*b, *x0)), true);
			return 1;
    }

		LUNAR_DECLARE(ConjugateGradient);
	};

  typedef ConjugateGradient<Matrix1f> ConjugateGradient1f;
  typedef ConjugateGradient<Matrix2f> ConjugateGradient2f;
  typedef ConjugateGradient<Matrix3f> ConjugateGradient3f;
  typedef ConjugateGradient<Matrix4f> ConjugateGradient4f;
  typedef ConjugateGradient<MatrixXf> ConjugateGradientXf;
}

#endif
