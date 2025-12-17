import ast
import dis

code = 'a = b + c'
tree = ast.parse(code)
print(ast.dump(tree))

def add(b, c):
    return b + c

dis.dis(add)
