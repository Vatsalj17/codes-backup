#include <ctype.h>
#include <string.h>

#include "conversions.h"
#include "utils.h"
#include "stack.h"
#include "stack2.h"

void reverse(char* str) {
	int i = 0;
	int j = strlen(str) - 1;
	while (i < j) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		j--;
		i++;
	}
}

char* infix_to_prefix(const char* infix) {
	int n = strlen(infix);

	char* tmp = strdup(infix);
	reverse(tmp);
	for (int i = 0; i < n; i++) {
		if (tmp[i] == '(')
			tmp[i] = ')';
		else if (tmp[i] == ')')
			tmp[i] = '(';
	}

	stack_t* prefix = stack_init(n);
	stack_t* operators = stack_init(n);

	for (int i = 0; i < n; i++) {
		if (isspace(tmp[i])) continue;
		if (isalnum(tmp[i]))
			push(prefix, tmp[i]);
		else {
			if (tmp[i] == '(') {
				push(operators, tmp[i]);
			} else if (tmp[i] == ')') {
				while (!isEmpty(operators) && peek(operators) != '(') {
					char temp;
					if ((temp = pop(operators)) == EMPTY) err("Wrong Paranthesis");
					push(prefix, temp);
				}
				pop(operators);
			} else {
				int index = precedence(tmp[i]);
				if (index == -1) err("Invalid Operator Found!");
				if (isEmpty(operators)) {
					push(operators, tmp[i]);
					continue;
				}
				while (!isEmpty(operators) &&
					   peek(operators) != '(' &&
					   (precedence(peek(operators)) > index ||
						(precedence(peek(operators)) == index && is_right_associative(tmp[i])))) {
					push(prefix, pop(operators));
				}
				push(operators, tmp[i]);
			}
		}
	}
	char temp;
	while ((temp = pop(operators)) != EMPTY) {
        if (temp == '(') err("Wrong Paranthesis");
		push(prefix, temp);
	}

    char* answer = get_string(prefix);
    free(tmp);
    destroy(prefix);
    destroy(operators);

	reverse(answer);

	return answer;
}

char* postfix_to_prefix(const char* postfix) {
	int n = strlen(postfix);
    stack_s* st = stacks_init(n);

    for (int i = 0; i < n; i++) {
        if (isspace(postfix[i])) continue;
        if (isalnum(postfix[i])) {
            char str[2] = {postfix[i], '\0'};
            pushs(st, str);
        } else {
            if (size(st) < 2) err("invalid postfix!");
            char* tmp1 = pops(st);
            char* tmp2 = pops(st);
            char op[2] = {postfix[i], '\0'};
            size_t len = strlen(tmp1) + strlen(tmp2) + 2;
            char* str = calloc(len, sizeof(char));
            strcat(str, op);
            strcat(str, tmp2);
            strcat(str, tmp1);
            pushs(st, str);
            free(str);
        }
    }
    if (size(st) != 1) err("postfix_to_infix failed!");
    char* prefix = strdup(pops(st));
    destroys(st);
    return prefix;
}
