# wap to check weather the entered number is even or odd
n = int(input("Enter a number: "))

if n & 1:
    print(n, "is odd")
else:
    print(n, "is even")

# wap with elif
age = int(input("Enter you age: "))

if age < 13:
    print("Child")
elif age < 20:
    print("Teenager")
elif age < 60:
    print("Adult")
else:
    print("Senior")

