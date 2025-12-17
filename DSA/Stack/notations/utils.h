#ifndef UTIL_H
#define UTIL_H

void err(char* msg);
int precedence(char op);
int isOperator(char c);
int is_right_associative(char op);

#endif
