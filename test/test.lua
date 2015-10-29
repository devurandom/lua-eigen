local eigen = require "eigen"

local mi = eigen.Matrix4f(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
)
local md = eigen.Matrix4f(
	2, 0, 0, 0,
	0, 3, 0, 0,
	0, 0, 4, 0,
	0, 0, 0, 5
)
local m1 = eigen.Matrix4f(
	0, 2, 3, 4,
	0, 0, 5, 6,
	0, 0, 0, 7,
	0, 0, 0, 0
)
local m2 = eigen.Matrix4f(
	0, 0, 19, 21,
	0, 0, 0, 27,
	0, 0, 0, 0,
	0, 0, 0, 0
)
local m1xm2 = eigen.Matrix4f(
	0, 0, 0, 54,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
)
local m2xm1 = eigen.Matrix4f(
	0, 0, 0, 133,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
)

print("md",md)
print("md*mi",md*mi)
print("mi*md",mi*md)

print("m1",m1)
print("m2",m2)
print("m1*m2",m1*m2)
print("expected:",m1xm2)
print("m2*m1",m2*m1)
print("expected:",m2xm1)
