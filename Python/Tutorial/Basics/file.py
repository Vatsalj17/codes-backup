file = open("file.txt", "w")

try:
    file.write("Content from file.py")
finally:
    file.close()


with open("file.txt", "w") as file:
    file.write('using with as')
