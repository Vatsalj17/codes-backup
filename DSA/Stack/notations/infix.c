#include <ctype.h>
#include <string.h>

#include "conversions.h"
#include "stack2.h"
#include "utils.h"

char* postfix_to_infix(const char* postfix) {
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
            size_t len = strlen(tmp1) + strlen(tmp2) + 4;
            char* str = calloc(len, sizeof(char));
            strcat(str, "(");
            strcat(str, tmp2);
            strcat(str, op);
            strcat(str, tmp1);
            strcat(str, ")");
            pushs(st, str);
            free(str);
        }
    }
    if (size(st) != 1) err("postfix_to_infix failed!");
    char* infix = strdup(pops(st));
    destroys(st);
    return infix;
}

char* prefix_to_infix(const char* prefix) {
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
            size_t len = strlen(tmp1) + strlen(tmp2) + 4;
            char* str = calloc(len, sizeof(char));
            strcat(str, "(");
            strcat(str, tmp1);
            strcat(str, op);
            strcat(str, tmp2);
            strcat(str, ")");
            pushs(st, str);
            free(str);
        }
    }
    if (size(st) != 1) err("prefix_to_infix failed!");
    char* infix = strdup(pops(st));
    destroys(st);
    return infix;
}
