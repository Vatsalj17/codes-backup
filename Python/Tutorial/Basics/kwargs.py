def printKwargs(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

printKwargs(name = "Shaktiman", power = "Lazer")
print()
printKwargs(name = "Shaktiman", power = "Lazer", enemy = "Dr. Jakaal")
