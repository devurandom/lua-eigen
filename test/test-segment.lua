local eigen = require "eigen"

local v = eigen.VectorXf(4)
for i=1,4 do v[i] = i end
print(v)
assert(v[1] == 1, "v[1] == 1")
assert(v[2] == 2, "v[2] == 2")

local s_1 = v.segment2[1]
print(s_1)
assert(s_1[1] == 1, "s_1[1] == 1")
assert(s_1[2] == 2, "s_1[2] == 2")

v.segment2[1] = eigen.Vector2f(5, 6)
print(v)
assert(v[1] == 5, "v[1] == 5")
assert(v[2] == 6, "v[2] == 6")

local s_2 = v.segment2[1]
print(s_2)
assert(s_2[1] == 5, "s_2[1] == 5")
assert(s_2[2] == 6, "s_2[2] == 6")
