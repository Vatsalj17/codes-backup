#include <stdio.h>
#include <stdlib.h>

void pattern1(int n) {
    char ch = 'a' - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        ch += i + 1;
        char temp = ch;
        for (int j = 0; j < i + 1; j++) {
            printf("%c", temp--);
        }
        printf("\n");
    }
}

void pattern2(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			printf("*");
		}
		printf("\n");
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i + 1; j++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * (n - i) - 1; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void pattern3(int n) {
	int idx = n - 1;
	for (int i = -idx; i <= idx; i++) {
		int row = abs(i);
		for (int j = 0; j < row; j++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * (n - row) - 1; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void pattern4(int n) {
	int idx = n - 1;
	for (int y = idx; y >= -idx; y--) {
        for (int x = -idx; x <= idx; x++) {
            int s = x + y;
            int d = x - y;
            if (s <= idx && s >= -idx && d >= -idx && d <= idx) {
                printf("*");
            } else {
                printf(" ");
            }
        }
		printf("\n");
	}
}

int main(void) {
	int n;
	printf("Enter number: ");
	scanf("%d", &n);
	pattern1(n);
}
