#include <stdio.h>

int main(void) {
	int r1, c1, r2, c2;
	printf("Enter no. of rows and columns for first matrix: ");
	scanf("%d%d", &r1, &c1);
	printf("Enter no. of rows and columns for second matrix: ");
	scanf("%d%d", &r2, &c2);
	if (c1 != r2) {
		printf("Not a valid matrix multiplication");
		return 1;
	}
	int matrix1[r1][c1];
	int matrix2[r2][c2];
	printf("Enter the first matrix:\n");
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			scanf("%d", &matrix1[i][j]);
		}
	}
	printf("Enter the second matrix:\n");
	for (int i = 0; i < r2; i++) {
		for (int j = 0; j < c2; j++) {
			scanf("%d", &matrix2[i][j]);
		}
	}
	printf("Product of the matrix:\n");
	int product[r1][c2];
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			product[i][j] = 0;
			for (int k = 0; k < c1; k++) {
				product[i][j] += matrix1[i][k] * matrix2[k][j];
			}
			printf("%d ", product[i][j]);
		}
		printf("\n");
	}
}
