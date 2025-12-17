#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INCORRCT
// char *removeOccurance(char *s, char *part) {
// 	int n = strlen(s);
// 	int p = strlen(part);
// 	char *ans = malloc(n * sizeof(char));
//     int out = 0;
// 	bool check = true;
// 	while (check) {
//         int idx = 0;
//         check = false;
//         if (n < p) break;
// 		for (int i = 0; i < n - p + 1; i++) {
//             char temp[100];
// 			strncpy(temp, s + i, p);
// 			if (strcmp(temp, part) == 0) {
//                 check = true;
// 				i += p;
// 			}
// 			ans[idx++] = s[i];
//             out = i;
// 		}
// 		for (int i = out + 1; i < n; i++) ans[idx++] = s[i];
//         ans[idx] = '\0';
//         n = strlen(ans);
//         if (check) s = ans;
// 	}
// 	return s;
// }

// char *removeOccurance(char *s, char *part) {
// 	int n = strlen(s);
// 	int p = strlen(part);
// 	if (p == 0) return s;
// 	char *ans = malloc((n + 1) * sizeof(char));
// 	if (!ans) return s;
// 	while (n >= p) {
// 		int idx = 0;
// 		int found = -1;
// 		if (n < p) break;
// 		int i;
// 		for (i = 0; i <= n - p; i++) {
// 			if (strncmp(s + i, part, p) == 0) {
// 				found = i;
// 				break;
// 			}
// 		}
//         if (found == -1) break;
// 		for (int i = 0; i < found; ++i) ans[idx++] = s[i];
// 		for (int i = found + p; i < n; ++i) ans[idx++] = s[i];
// 		ans[idx] = '\0';
// 		n = idx;
// 		memcpy(s, ans, n + 1);
// 	}
// 	free(ans);
// 	return s;
// }

char *removeOccurance(char *s, char *part) {
    if (!s || !part) return s;
	size_t p = strlen(part);
	if (p == 0) return s;
    char *pos;
    while((pos = strstr(s, part)) != NULL) {
        size_t idx = pos - s;
        size_t n = strlen(s);
        memmove(s + idx, s + idx + p, n - idx - p + 1);
    }
	return s;
}

int main(void) {
	char s[100], part[100];
	printf("Enter the string: ");
	fgets(s, 100, stdin);
	s[strlen(s) - 1] = '\0';
	printf("Enter the part: ");
	fgets(part, 100, stdin);
	part[strlen(part) - 1] = '\0';
	char *ans = removeOccurance(s, part);
	printf("%s\n", ans);
}
