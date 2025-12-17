#include <math.h>
#include <stdio.h>

void square(int n);
void sq_area(int n);
void cir_area(int n);
void rec_area(float n, float m);
float percentage(float p, float q, float r);
void star(int n);

int main() {
	int s;
	float a, b;
	printf("Enter a number : ");
	scanf("%d", &s);
	printf("Enter Length: ");
	scanf("%f", &a);
	printf("Enter breadth: ");
	scanf("%f", &b);
	square(s);
	rec_area(a, b);
	printf("%f", percentage(s, a, b));
	star(s);
	return 0;
}

void square(int n) {
	n = n * n;
	printf("Square of the number is %d\n", n);
}

void sq_area(int n) { printf("Area of square is %f\n", pow(n, 2)); }

void cir_area(int n) { printf("Area of circle is %f\n", (float)n * n * 22 / 7); }

void rec_area(float n, float m) { printf("Area of rectangle is %f\n", m * n); }

float percentage(float p, float q, float r) {
	int t = (p + q + r) / 3;
	return t;
}

void star(int n) {
	for (int i = 1; i <= 1 + (n - 1) * 2; i = i + 2) {
		for (int k = 1; k <= i; k++) {
			printf("*");
		}
		printf("\n");
		printf(" \n");
	}
}
