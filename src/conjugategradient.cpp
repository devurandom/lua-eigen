#include "conjugategradient.hpp"

#define CONJUGATEGRADIENT_METHODS(type) \
  LUNAR_METHOD(type, compute), \
  LUNAR_METHOD(type, solve), \
  LUNAR_METHOD(type, solveWithGuess)

namespace LuaEigen {
  template<>
	const char ConjugateGradient1f::className[] = "ConjugateGradient1f";
	template<>
	const LunarType<ConjugateGradient1f>::Reg ConjugateGradient1f::methods[] = {
    CONJUGATEGRADIENT_METHODS(ConjugateGradient1f),
		{NULL, NULL}
	};
  template<>
	const char ConjugateGradient2f::className[] = "ConjugateGradient2f";
	template<>
	const LunarType<ConjugateGradient2f>::Reg ConjugateGradient2f::methods[] = {
    CONJUGATEGRADIENT_METHODS(ConjugateGradient2f),
		{NULL, NULL}
	};
  template<>
	const char ConjugateGradient3f::className[] = "ConjugateGradient3f";
	template<>
	const LunarType<ConjugateGradient3f>::Reg ConjugateGradient3f::methods[] = {
    CONJUGATEGRADIENT_METHODS(ConjugateGradient3f),
		{NULL, NULL}
	};
  template<>
	const char ConjugateGradient4f::className[] = "ConjugateGradient4f";
	template<>
	const LunarType<ConjugateGradient4f>::Reg ConjugateGradient4f::methods[] = {
    CONJUGATEGRADIENT_METHODS(ConjugateGradient4f),
		{NULL, NULL}
	};
  template<>
	const char ConjugateGradientXf::className[] = "ConjugateGradientXf";
	template<>
	const LunarType<ConjugateGradientXf>::Reg ConjugateGradientXf::methods[] = {
    CONJUGATEGRADIENT_METHODS(ConjugateGradientXf),
		{NULL, NULL}
	};
}
