#include <stdio.h>

int main(void) {
    char name[10];
    int number = 42;
    printf("Enter: ");
    scanf("%s", name);
    printf("name: %s, number: %d\n", name, number);
}
