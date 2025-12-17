#include <stdio.h>

int main(void) {
    // int a = 5, b = 6, c;
    // c = ++a + a++ + ++ a + a++ + ++b + b++ + ++a + b++ + ++b + ++b + b++ + ++a;
    // printf("a: %d, b: %d, c: %d\n", a, b, c);
    int a = 7;
    printf("%d %d %d %d\n", ++a, a++, ++a, a++);
    printf("%%%");
}
