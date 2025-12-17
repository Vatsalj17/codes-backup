numbers = [1, -2, 3, -4, 5, 6, -7, -8, 9, 10]
posNums = 0
for num in numbers:
    if num > 0:
        posNums += 1
print("There are", posNums, "Positive numbers")

n = int(input("Enter a number: "))
evenSum = 0
for i in range(1, n + 1):
    if i & 1 == 0:
        evenSum += i
print("Sum of even number upto", n, "is", evenSum)
