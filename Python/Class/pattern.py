# Patterns->
# triangle
# nepal flag
# diamond 

n = int(input("Enter a number: "))
print("Nepal Flag:")
for i in range(0, n):
    for j in range(0, i + 1):
        print("*", end="")
    print()
for i in range(0, n):
    for j in range(0, i + 1):
        print("*", end="")
    print()

print()
print()

print("Triangle:")
for i in range(0, n):
    for j in range(0, n - i):
        print(" ", end="")
    for j in range(0, 2*i + 1):
        print("*", end="")
    print()

print()
print()

print("Diamond:")
for i in range(0, n):
    for j in range(0, n - i):
        print(" ", end="")
    for j in range(0, 2*i + 1):
        print("*", end="")
    print()
for i in range(1, n):
    for j in range(0, i + 1):
        print(" ", end="")
    for j in range(0, 2*(n - i) - 1):
        print("*", end="")
    print()

