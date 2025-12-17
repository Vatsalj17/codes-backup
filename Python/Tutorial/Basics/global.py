x = 1
def fun():
    global x
    x = 4
    print(x)

print(x)
fun()
print(x)

def f1():
    x = 9
    def f2():
        print(x)
    return f2

h = f1()
h()
