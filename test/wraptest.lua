if not arg[1] then
	error("Usage: " .. arg[0] .. " <test-case>")
end
local chunk = loadfile("test/test-" .. arg[1] .. ".lua")
local STP = require "StackTracePlus"
local success, err = xpcall(chunk, STP.stacktrace)
if not success then
	print(err)
end
