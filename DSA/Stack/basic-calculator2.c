#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#define EMPTY CHAR_MAX

typedef struct Stack {
    char *data;
    int sp;
    size_t capacity;
} stack_t;

stack_t* stack_init(size_t size) {
    stack_t* stack = malloc(sizeof(stack_t));
    stack->data = calloc(size + 1, sizeof(char));
    stack->sp = -1;
    stack->capacity = size;
    return stack;
}

bool isEmpty(stack_t* stack) {
    if (stack->sp > -1) return false;
    return true;
}

bool isFull(stack_t* stack) {
    if (stack->sp >= (int)stack->capacity - 1) return true;
    return false;
}

bool push(stack_t* stack, char value) {
    if (stack == NULL || isFull(stack)) return false;
    stack->data[++stack->sp] = value;
    return true;
}

char pop(stack_t* stack) {
    if (stack == NULL || isEmpty(stack)) return EMPTY;
    char value = stack->data[stack->sp--];
    return value;
}

char peek(stack_t* stack) {
    if (stack == NULL || isEmpty(stack)) return EMPTY;
    return stack->data[stack->sp];
}

void destroy(stack_t* stack) {
    free(stack->data);
    free(stack);
}

char* get_string(stack_t* stack) {
    char* answer = strdup(stack->data);
    return answer;
}

int precedence(char op) {
	if (op == '-' || op == '+') return 0;
	if (op == '*' || op == '/') return 1;
	if (op == '^') return 2;
	return -1;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int is_right_associative(char op) { return op == '^'; }

void err(char* msg) {
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

char* infix_to_postfix(const char* infix) {
	int n = strlen(infix);
	stack_t* postfix = stack_init(n);
	stack_t* operators = stack_init(n);

	for (int i = 0; i < n; i++) {
		if (isspace(infix[i])) continue;
		if (isalnum(infix[i]))
			push(postfix, infix[i]);
		else {
			if (infix[i] == '(') {
				push(operators, infix[i]);
			} else if (infix[i] == ')') {
				while (!isEmpty(operators) && peek(operators) != '(') {
					char temp;
					if ((temp = pop(operators)) == EMPTY) err("Wrong Paranthesis");
					push(postfix, temp);
				}
				pop(operators);
			} else {
				int index = precedence(infix[i]);
				if (index == -1) err("Invalid Operator Found!");
				if (isEmpty(operators)) {
					push(operators, infix[i]);
					continue;
				}
				while (!isEmpty(operators) &&
					   peek(operators) != '(' &&
					   (precedence(peek(operators)) > index ||
						(precedence(peek(operators)) == index && !is_right_associative(infix[i])))) {
					push(postfix, pop(operators));
				}
				push(operators, infix[i]);
			}
		}
	}
	char temp;
	while ((temp = pop(operators)) != EMPTY) {
        if (temp == '(') err("Wrong Paranthesis");
		push(postfix, temp);
	}

    char* answer = get_string(postfix);
    destroy(postfix);
    destroy(operators);
    return answer;
}

int calculate(char* s) {
    char* postfix = infix_to_postfix(s);
    printf("%s %ld\n", s, strlen(s));
    printf("%s %ld\n", postfix, strlen(postfix));
    int n = strlen(postfix);
    int* stack = malloc(n * sizeof(int));
    int sp = -1;
    for (int i = 0; i < n; i++) {
        if (isOperator(postfix[i])) {
            int num1 = stack[sp];
            int num2 = stack[sp - 1];
            int result;
            switch (postfix[i]) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num2 / num1;
                break;
            }
            sp--;
            stack[sp] = result;
        } else if (isdigit(postfix[i])) {
            stack[++sp] = postfix[i] - '0';
        }
    }
    int ans = stack[0];
    free(stack);
    return ans;
}
