import time

def timer(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(f"{func.__name__} ran in {end - start} time")
        return result
    return wrapper

@timer # adding this decorator makes sure that the next line function first passes through the decorator function
def example(n):
    time.sleep(n)

# example(5)

#-----------------------------#

def debug(func):
    def wrapper(*args, **kwargs):
        args_value = ', '.join(str(arg) for arg in args)
        kwargs_value = ', '.join(f"{k}: {v}" for k, v in kwargs.items())
        print(f"Calling \"{func.__name__}\" with args \"{args_value}\" and kwargs \"{kwargs_value}\"")
        return func(*args, **kwargs)
    return wrapper

@debug
def hello():
    print("Hello!")

@debug
def greet(name, greeting="Hello"):
    print(f"{greeting}! {name}")

hello()
greet("Vatsal", "Namaste")
