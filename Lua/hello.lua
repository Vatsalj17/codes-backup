local function greet(name)
	print ("Hello " .. name)
end
print ("Enter you name: ")
local name = io.read()
if name == "Vatsal" then
	greet(name)
else
	print ("Wrong User")
end
