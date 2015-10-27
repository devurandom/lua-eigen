local eigen = require "eigen"

local A = eigen.MatrixXf(2,2)
A(1,1,4)
A(1,2,1)
A(2,1,1)
A(2,2,3)

local b = eigen.VectorXf(2)
b(1,1,1)
b(2,1,2)

local x0 = eigen.VectorXf(2)
x0(1,1,2)
x0(2,1,1)

local x = eigen.VectorXf(2)
x(1,1,1/11)
x(2,1,7/11)

print("A",A)
print("b",b)
print("x0",x0)

local cg = eigen.ConjugateGradientXf()
print("x", cg:compute(A):solveWithGuess(b, x0))
print("expected:", x)
