#include <ctype.h>
#include <string.h>

#include "conversions.h"
#include "stack.h"
#include "stack2.h"
#include "utils.h"

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

char* prefix_to_postfix(const char* prefix) {
	int n = strlen(prefix);
    stack_s* st = stacks_init(n);

    for (int i = n - 1; i >= 0; i--) {
        if (isspace(prefix[i])) continue;
        if (isalnum(prefix[i])) {
            char str[2] = {prefix[i], '\0'};
            pushs(st, str);
        } else {
            if (size(st) < 2) err("invalid prefix!");
            char* tmp1 = pops(st);
            char* tmp2 = pops(st);
            char op[2] = {prefix[i], '\0'};
            size_t len = strlen(tmp1) + strlen(tmp2) + 2;
            char* str = calloc(len, sizeof(char));
            strcat(str, tmp1);
            strcat(str, tmp2);
            strcat(str, op);
            pushs(st, str);
            free(str);
        }
    }
    if (size(st) != 1) err("prefix_to_postfix failed!");
    char* postfix = strdup(pops(st));
    destroys(st);
    return postfix;

}
