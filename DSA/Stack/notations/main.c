#include <stdio.h>

#include "conversions.h"

int main(void) {
	// char *infix = "a*(b+c)/d";
	char *infix = "(a+b)*c-d+f";
	char *infix2 = "a+b*(c^d-e)";
	char* postfix = "ab-de+f*/";
    char* prefix = "*+pq-mn";
    char* prefix2 = "/-ab*+def";
	printf("infix to postfix-->  %s\n", infix_to_postfix(infix2));
	printf("infix to prefix-->  %s\n", infix_to_prefix(infix));
    printf("postfix to infix-->  %s\n", postfix_to_infix(postfix));
    printf("prefix to infix-->  %s\n", prefix_to_infix(prefix));
    printf("postfix to prefix-->  %s\n", postfix_to_prefix(postfix));
    printf("prefix to postfix-->  %s\n", prefix_to_postfix(prefix2));
}
