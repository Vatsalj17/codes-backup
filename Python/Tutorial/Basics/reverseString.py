str = input("Enter a string: ")
revStr = ""

for char in str:
    revStr = char + revStr

print("reverse:", revStr)


# First non-repeated character
for char in str:
    if str.count(char) == 1:
        print("First non-repeated char:",char)
        break
