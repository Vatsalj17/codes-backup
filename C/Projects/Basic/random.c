#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[1024] = {0};
    char *str = "Hello";
    char hi = 65;
    strcat(buf, str);
    fputs(buf, stdout);
    printf("\n%s\n", buf);
    printf("%c\n", hi);
}
