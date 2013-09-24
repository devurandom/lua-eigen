local eigen = require "eigen"

local q = eigen.Quaternionf(1,2,3,4)
local v = {1,2,3}
for i,j in ipairs(q*v) do
	print(j)
end
