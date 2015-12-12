---[[
local hello = require "hello_lib"
print(hello.hello_sin(1))
t = {1, 2, 3}
function f(a)
	return a+1
end
hello.l_map(t, f)
for i = 1, #t do
	print(t[i])
end
--]]
