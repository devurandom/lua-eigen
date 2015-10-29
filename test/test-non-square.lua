local eigen = require "eigen"

local m1 = eigen.Matrix24f(
	1, 0, 0, 0,
	0, 1, 0, 0
)
local m2 = eigen.Matrix42f(
	2, 0,
	0, 3,
	0, 0,
	0, 0
)
local m1xm2 = eigen.Matrix2f(
	2, 0,
	0, 3
)

print("m1",m1)
print("m2",m2)
print("m1*m2",m1*m2)
print("expected:",m1xm2)
