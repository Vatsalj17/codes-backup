#include <stdio.h>

int main() {
    int a,b;
    FILE *f;
    f = fopen("sum.txt", "r");
    fscanf(f, "%d", &a);
    fscanf(f, "%d", &b);
    fclose(f);
    int c = a+b;
    f = fopen("sum.txt", "w");
    fprintf(f, "%d", c);
    fclose(f);
    return 0;
}