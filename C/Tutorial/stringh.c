#include <string.h>
#include <stdio.h>

int main(void)
{
    int str[100];
    fgets(str, 100, stdin);
    printf("Length: %d", strlen(str));
    int str2[100] = "Hello";
    strcat(str, str2);
}