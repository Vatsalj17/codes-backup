#include <stdio.h>

int main(void) {
    char p[] = "gate2020";
    printf("%s", p + p[3] - p[1]);
}
