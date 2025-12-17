#include <stdio.h>

int main(void) {
    char *h = "what are you doing i am not okay";
    for (int i = 0; h[i] != '\0'; i++) {
        if (h[i] == '"') {
            printf("found it at %d\n", i);
        }
    }
}
