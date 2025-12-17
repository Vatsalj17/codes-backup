#include <stdio.h>
#include <string.h>

int main (void) {
    char str[] = "abc123def567";
    puts(str);
    char str2[] = "zxc";
    char *mat = strpbrk(str, str2);
    printf("%s", mat);
}
