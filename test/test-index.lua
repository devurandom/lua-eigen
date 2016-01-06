local eigen = require "eigen"

print("Matrix4f")

local m = eigen.Matrix4f(
	 1, 2, 3, 4,
	 5, 6, 7, 8,
	 9,10,11,12,
	13,14,15,16
)
print(m)
assert(m{2,3} == 7, "m{2,3} == 7")

m:set({2,3}, 21)
print(m)
assert(m{2,3} == 21, "m{2,3} == 21")

print("MatrixXf")

local mx = eigen.MatrixXf(4, 4)
for i=1,4 do for j=1,4 do mx[{i,j}] = (i-1)*4 + j end end
print(mx)
assert(mx{2,3} == 7, "mx{2,3} == 7")

mx:set({2,3}, 21)
print(mx)
assert(mx{2,3} == 21, "mx{2,3} == 21")

print("Vector4f")

local v = eigen.Vector4f(1, 2, 3, 4)
print(v)
assert(v(2) == 2, "v(2) == 2")
assert(v{2,1} == 2, "v{2,1} == 2")

v:set(2, 31)
print(v)
assert(v(2) == 31, "v(2) == 31")
assert(v{2,1} == 31, "v{2,1} == 31")

v:set({2,1}, 21)
print(v)
assert(v(2) == 21, "v(2) == 21")
assert(v{2,1} == 21, "v{2,1} == 21")

print("VectorXf")

local vx = eigen.VectorXf(4)
for i=1,4 do vx:set({i, 1}, i) end
print(vx)
assert(vx(2) == 2, "vx(2) == 2")
assert(vx{2,1} == 2, "vx{2,1} == 2")

vx:set(2, 31)
print(vx)
assert(vx(2) == 31, "vx(2) == 31")
assert(vx{2,1} == 31, "vx{2,1} == 31")

vx:set({2,1}, 21)
print(vx)
assert(vx(2) == 21, "vx(2) == 21")
assert(vx{2,1} == 21, "vx{2,1} == 21")
