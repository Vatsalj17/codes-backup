#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int precedence(char op) {
	if (op == '-' || op == '+') return 0;
	if (op == '*' || op == '/') return 1;
	if (op == '^') return 2;
	return -1;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void err(char* msg) {
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int is_right_associative(char op) { return op == '^'; }
