#include <stdio.h>

int add(int a, int b) { return a + b; }
int mult(int a, int b) { return a * b; }

/*
// Without typedef
int do_operation(int (*op)(int, int), int x, int y) {
	return op(x, y);
}

int main() {
	int (*operation)(int, int);
	operation = add;
	printf("add: %d\n", do_operation(operation, 5, 3));
	printf("mult: %d\n", do_operation(mult, 5, 3));
	return 0;
}
*/

// With typedef
typedef int (*operation_ptr) (int, int);

int do_operation(operation_ptr op, int x, int y) {
	return op(x, y);
}

int main() {
    operation_ptr operation = add;
	printf("add: %d\n", do_operation(operation, 5, 3));
	printf("mult: %d\n", do_operation(mult, 5, 3));
	return 0;
}
