#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// char *removeDuplicate(char *s) {
// 	if (!s) return s;
// 	bool found = true;
// 	while (found) {
// 		found = false;
//         int n = strlen(s);
//         if (n < 2) break;
// 		for (int i = 1; i < n; i++) {
// 			if (s[i - 1] == s[i]) {
// 				memmove(s + i - 1, s + i + 1, n - i);
// 				found = true;
//                 break;
// 			}
// 		}
// 	}
// 	return s;
// }

char *removeDuplicate(char *s) {
	if (!s) return s;
    int n = strlen(s), w = 0;
    for (int r = 0; r < n; r++) {
        s[w++] = s[r];
        if (w >= 2 && s[w - 1] == s[w - 2]) w -= 2;
    }
    s[w] = '\0';
	return s;
}

int main() {
	printf("Enter a string: ");
	char s[100];
	scanf("%s", s);
	char *ans = removeDuplicate(s);
	printf("%s\n", ans);
	return 0;
}
