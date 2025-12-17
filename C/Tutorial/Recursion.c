#include <stdio.h>
#include <stdlib.h>

int sumn(int n);
int fibonacci(int n);
int func(int n);
int hcf(int a, int b);
int expo(int a, int b);
void tower_of_hanoi(int n, char ch);
void reverse_array(int rev[], int n, int q);

int main() {
	int n;
	printf("Enter length of the array: ");
	scanf("%d", &n);
	int *rev = (int *)malloc(n * sizeof(int));
	for (int l = 0; l < n; l++) {
		printf("rev[%d] = ", l);
		scanf(" %d", &rev[l]);
	}
	reverse_array(rev, n, n);
	for (int k = 0; k < n; k++) {
		printf("%d ", rev[k]);
	}
	printf("\n");
	printf("Enter a number for fibonacci series: ");
	int m;
	printf("Enter a number to find the hcf of it with above number: ");
	scanf("%d", &m);
	if (n >= 1) {
		for (int i = 1; i <= n; i++) {
			int f = fibonacci(i);
			printf("%d ", f);
		}
	} else {
		printf("error");
	}
	printf("\nhcf = %d", hcf(n, m));
	return 0;
}

void reverse_array(int rev[], int n, int q) {
	if (n <= q / 2) {
		return;
	} else {
		int t = rev[q - n];
		rev[q - n] = rev[n - 1];
		rev[n - 1] = t;
		reverse_array(rev, n - 1, q);
	}
}

void tower_of_hanoi(int n, char ch) {
	if (n == 1) {
		// printf("\nMove the disk from %c to %c");
	}
}

int expo(int a, int b) {
	if (b == 0) {
		return 1;
	} else {
		return a * expo(a, b - 1);
	}
}

int hcf(int a, int b) {
	if (b >= a) {
		if (b % a == 0) {
			return a;
		} else {
			hcf(a, b % a);
		}
	} else {
		if (a % b == 0) {
			return b;
		} else {
			hcf(b, a % b);
		}
	}
	return 0;
}

int func(int n) {
	if (n == 0) {
		return 0;
	} else {
		return (func(n - 1));
	}
}

int sumn(int n) {
	int s;
	if (n == 1) {
		return 1;
	} else {
		s = n + sumn(n - 1);
		return s;
	}
}

int fibonacci(int n) {
	if (n == 1) {
		return 0;
	} else if (n == 2) {
		return 1;
	} else if (n >= 3) {
		int f = fibonacci(n - 1) + fibonacci(n - 2);
		return f;
	}
	return 0;
}
