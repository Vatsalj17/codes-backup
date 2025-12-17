filename = "example.txt"
file = open(filename, "a")
file.write("New line appended by code")
file.close()

file = open(filename, "r")
print("Reading content of file:")
buffer = file.read()
print(buffer)
file.close()

file = open(filename, "r")
line1 = file.readline()
print("\nFirst line of file => ", line1)
line2 = file.readline()
print("Second line of file => ", line2)
file.close()
