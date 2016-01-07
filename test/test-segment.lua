local eigen = require "eigen"

print("segment2")

local v1 = eigen.VectorXf(4)
for i=1,4 do v1:set(i, i) end
print(v1)
assert(v1(1) == 1, "v1(1) == 1")
assert(v1(2) == 2, "v1(2) == 2")
assert(v1(3) == 3, "v1(3) == 3")
assert(v1(4) == 4, "v1(4) == 4")

local s2_1 = v1.segment2[1]
print(s2_1)
assert(s2_1(1) == 1, "s2_1(1) == 1")
assert(s2_1(2) == 2, "s2_1(2) == 2")

local s2_3 = v1.segment2[3]
print(s2_3)
assert(s2_3(1) == 3, "s2_3(1) == 3")
assert(s2_3(2) == 4, "s2_3(2) == 4")

v1.segment2[1] = eigen.Vector2f(5, 6)
print(v1)
assert(v1(1) == 5, "v1(1) == 5")
assert(v1(2) == 6, "v1(2) == 6")
assert(v1(3) == 3, "v1(3) == 3")
assert(v1(4) == 4, "v1(4) == 4")

v1.segment2[3] = eigen.Vector2f(7, 8)
print(v1)
assert(v1(1) == 5, "v1(1) == 5")
assert(v1(2) == 6, "v1(2) == 6")
assert(v1(3) == 7, "v1(3) == 7")
assert(v1(4) == 8, "v1(4) == 8")

local s2_1_2 = v1.segment2[1]
print(s2_1_2)
assert(s2_1_2(1) == 5, "s2_1_2(1) == 5")
assert(s2_1_2(2) == 6, "s2_1_2(2) == 6")

local s2_3_2 = v1.segment2[3]
print(s2_3_2)
assert(s2_3_2(1) == 7, "s2_3_2(1) == 7")
assert(s2_3_2(2) == 8, "s2_3_2(2) == 8")

print("segment3")

local v2 = eigen.VectorXf(6)
for i=1,6 do v2:set(i, i) end
print("v2", v2)
assert(v2(2) == 2, "v2(2) == 2")
assert(v2(3) == 3, "v2(3) == 3")
assert(v2(4) == 4, "v2(4) == 4")
assert(v2(5) == 5, "v2(5) == 5")
assert(v2(6) == 6, "v2(6) == 6")

local s3_1 = v2.segment3[1]
print("segment3[1]", s3_1)
assert(s3_1(1) == 1, "s3_1(1) == 1")
assert(s3_1(2) == 2, "s3_1(2) == 2")
assert(s3_1(3) == 3, "s3_1(3) == 3")

local s3_4 = v2.segment3[4]
print("segment3[4]", s3_4)
assert(s3_4(1) == 4, "s3_4(1) == 4")
assert(s3_4(2) == 5, "s3_4(2) == 5")
assert(s3_4(3) == 6, "s3_4(3) == 6")

v2.segment3[1] = eigen.Vector3f(5, 6, 7)
print("v2", v2)
assert(v2(1) == 5, "v2(1) == 5")
assert(v2(2) == 6, "v2(2) == 6")
assert(v2(3) == 7, "v2(3) == 7")
assert(v2(4) == 4, "v2(4) == 4")
assert(v2(5) == 5, "v2(5) == 5")
assert(v2(6) == 6, "v2(6) == 6")

v2.segment3[4] = eigen.Vector3f(8, 9, 10)
print("v2", v2)
assert(v2(1) == 5, "v2(1) == 5")
assert(v2(2) == 6, "v2(2) == 6")
assert(v2(3) == 7, "v2(3) == 7")
assert(v2(4) == 8, "v2(4) == 8")
assert(v2(5) == 9, "v2(5) == 9")
assert(v2(6) == 10, "v2(6) == 10")

local s3_1_2 = v2.segment3[1]
print("segment3[1]", s3_1_2)
assert(s3_1_2(1) == 5, "s3_1_2(1) == 5")
assert(s3_1_2(2) == 6, "s3_1_2(2) == 6")
assert(s3_1_2(3) == 7, "s3_1_2(3) == 7")

local s3_3_2 = v2.segment3[4]
print("segment3[4]", s3_3_2)
assert(s3_3_2(1) == 8, "s3_3_2(1) == 8")
assert(s3_3_2(2) == 9, "s3_3_2(2) == 9")
assert(s3_3_2(3) == 10, "s3_3_2(3) == 10")

print("segment3 - second")

local v3 = eigen.VectorXf(6)
for i=1,6 do v3:set(i, i) end
print("v3",v3)
assert(v3(1) == 1, "v3(1) == 1")
assert(v3(2) == 2, "v3(2) == 2")
assert(v3(3) == 3, "v3(3) == 3")
assert(v3(4) == 4, "v3(4) == 4")
assert(v3(5) == 5, "v3(5) == 5")
assert(v3(6) == 6, "v3(6) == 6")

v3.segment3[1] = eigen.Vector3f(11, 12, 13)
print("v3", v3)
assert(v3(1) == 11, "v3(1) == 11")
assert(v3(2) == 12, "v3(2) == 12")
assert(v3(3) == 13, "v3(3) == 13")
assert(v3(4) == 4, "v3(4) == 4")
assert(v3(5) == 5, "v3(5) == 5")
assert(v3(6) == 6, "v3(6) == 6")

v3.segment3[4] = eigen.Vector3f(14, 15, 16)
print("v3", v3)
assert(v3(1) == 11, "v3(1) == 11")
assert(v3(2) == 12, "v3(2) == 12")
assert(v3(3) == 13, "v3(3) == 13")
assert(v3(4) == 14, "v3(4) == 14")
assert(v3(5) == 15, "v3(5) == 15")
assert(v3(6) == 16, "v3(6) == 16")

print("segment3 - check first again")

print("v2", v2)
assert(v2(1) == 5, "v2(1) == 5")
assert(v2(2) == 6, "v2(2) == 6")
assert(v2(3) == 7, "v2(3) == 7")
assert(v2(4) == 8, "v2(4) == 8")
assert(v2(5) == 9, "v2(5) == 9")
assert(v2(6) == 10, "v2(6) == 10")

v2.segment3[1] = eigen.Vector3f(17, 18, 19)
print("v2/v3", v2, v3)
assert(v2(1) == 17, "v2(1) == 17")
assert(v2(2) == 18, "v2(2) == 18")
assert(v2(3) == 19, "v2(3) == 19")
assert(v2(4) == 8, "v2(4) == 8")
assert(v2(5) == 9, "v2(5) == 9")
assert(v2(6) == 10, "v2(6) == 10")

assert(v3(1) == 11, "v3(1) == 11")
assert(v3(2) == 12, "v3(2) == 12")
assert(v3(3) == 13, "v3(3) == 13")
assert(v3(4) == 14, "v3(4) == 14")
assert(v3(5) == 15, "v3(5) == 15")
assert(v3(6) == 16, "v3(6) == 16")
