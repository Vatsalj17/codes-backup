#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 20.
bool isValid(char *s) {
    char stack[strlen(s)];
    int sp = -1;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++sp] = s[i];
        } else {
            if (sp == -1) return false;
            char top = stack[sp];
            if ((top == '(' && s[i] == ')') || (top == '{' && s[i] == '}') || (top == '[' && s[i] == ']')) 
                sp--;
            else 
                return false;
        }
    }
    if (sp < 0) return false;
    return true;
}

int main(void) {
    if (isValid("[[[[[[[[[[[]]]]]]]]]]]")) printf("valid\n");
}
