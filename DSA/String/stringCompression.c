#include <stdio.h>
#include <stdlib.h>

int compress(char *chars, int charsSize) {
	int ans = 0;
	if (charsSize == 1) return 1;
	char *new = malloc(charsSize * sizeof(char));
	int boolean = 1;
	for (int i = 0; i < charsSize - 1; i++) {
		int count = 0;
		new[ans] = chars[i];
		ans++;
		while (i < charsSize - 1 && chars[i] == chars[i + 1]) {
			count++;
			i++;
		}
		char temp[10];
		sprintf(temp, "%d", count + 1);
		if (count > 0) {
			for (int i = 0; temp[i] != '\0'; i++)
				new[ans++] = temp[i];
		}
	}
    if (chars[charsSize - 1] !=  chars[charsSize - 2])
        new[ans] = chars[charsSize - 1];
	for (int i = 0; i < ans; i++) {
		chars[i] = new[i];
	}
    free(new);
	return ans;
}

int main(void) {
	int n;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	char *chars = malloc(n * sizeof(char));
	printf("Enter the array characters: ");
	for (int i = 0; i < n; i++) {
		scanf(" %c", &chars[i]);
	}
	int ans = compress(chars, n);
	printf("New length: %d\n", ans);
    printf("This is the ans: ");
    for (int i = 0; i < n; i++) {
        printf("%c", chars[i]);
    }
    printf("\n");
	free(chars);
	return 0;
}
