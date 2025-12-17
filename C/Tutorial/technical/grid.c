#include <stdio.h>

int main(void) {
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			// G
			// if (i == 0 || j == 0 || (i == 10 && j <= 5) || (j == 10 && i >= 5) || (j == 5 && i >= 5) || (i == 5 && j >= 5))
			// 	printf("*");

			if (((i == 0 || i == 3) && j >= 3 && j <= 7) 
                || ((j == 3 || j == 7) && i <= 3) 
                || (j == 5 && i >= 3 && i <= 8)
                || ((i == j) && j >= 5 && j <= 7))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}
