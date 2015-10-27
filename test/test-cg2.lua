local eigen = require "eigen"

local A = eigen.Matrix2f(
	4, 1,
	1, 3
)
local b = eigen.Vector2f(
	1,
	2
)
local x0 = eigen.Vector2f(
	2,
	1
)
local x = eigen.Vector2f(
	1/11,
	7/11
)

print("A",A)
print("b",b)
print("x0",x0)

local cg = eigen.ConjugateGradient2f()
print("x", cg:compute(A):solveWithGuess(b, x0))
print("expected:", x)
