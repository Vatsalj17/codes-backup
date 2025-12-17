def func(num):
    def actual(x):
        return x ** num
    return actual

n = func(2) # num
r = n(9) # x
print(r)
