#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	printf("Enter size: ");
	scanf("%d", &n);
	int *a = malloc(n * sizeof(int));
	int *b = malloc(n * sizeof(int));
    printf("Enter array: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    for (int i = 0; i < n; i++) {
        b[i] = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            b[i] *= a[j];
        }
    }
    printf("Product array: ");
    for (int i = 0; i < n; i++) printf("%d ", b[i]);
    printf("\n");
}
