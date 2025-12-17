#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int var (int num, ...) {
    va_list a;
    va_start(a, num);
    for (int i = 0; i < num; i++) {
        int x = va_arg(a, int); 
        printf("x: %d\n", x);
    }
    va_end(a);
    return 0;
}

int max (int n, ...) {
    va_list p;
    va_start(p, n);
    int maxim = va_arg(p, int);
    for (int i = 0; i < n; i++) {
         int a = va_arg(p, int);
         if ( a > maxim ) maxim = a;
    }
    va_end(p);
    return maxim;
}

void print (char *str, ...) {
    int n = strlen(str);
    va_list args;
    va_start(args, str);
    for (int i = 0; i < n; i++) {
        if (str[i] == 'd') 
            printf("%d ", va_arg(args, int));
        else if (str[i] == 'f')
            printf("%.2f ", va_arg(args, double));
    }
    va_end(args);
}
    

int main (void) {
    var(5, 4, 5, 3, 6, 7);
    printf("Max: %d\n", max(4, 1, 6, 23, 11));
    print("df", 4, 3.2);
}
