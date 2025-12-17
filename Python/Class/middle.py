# wap to find middle of a number
a = int(input("Enter a: "))
b = int(input("Enter b: "))
c = int(input("Enter c: "))

# mid = a + b + c - min(a, b, c) - max(a, b, c)
# print(mid)

if a > b:
    if b > c:
        print(b)
    elif a > c:
        print(c)
    else: 
        print(a)
else:
    if a > c:
        print(a)
    elif b > c:
        print(c)
    else: 
        print(b)
