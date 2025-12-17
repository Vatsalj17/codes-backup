#include "mycode.h"
#include <string.h>

char* reverse(char* string) {
    int n = strlen(string);
    for (int i = 0; i < n / 2; i++) {
        char temp = string[i];
        string[i] = string[n - i - 1];
        string[n - i - 1] = temp;
    }
    return string;
}
