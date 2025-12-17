#include <string.h>

#include "heap.h"

int main() {
	int* p1 = (int*)malloc(16);
	if (p1 == NULL) {
		return 1;
	}
	*p1 = 111;

	char* p2 = (char*)malloc(32);
	if (p2 == NULL) {
		free(p1);
		return 1;
	}
	p2[0] = 'A';

	free(p1);

	int* p3 = (int*)malloc(8);
	if (p3 == NULL) {
		free(p2);
		return 1;
	}
	*p3 = 333;

	free(p2);
	free(p3);

	int num_elements = 4;
	int* c1 = (int*)calloc(num_elements, sizeof(int));
	if (c1 == NULL) {
		return 1;
	}

	int all_zeros = 1;
	for (int i = 0; i < num_elements; i++) {
		if (c1[i] != 0) {
			all_zeros = 0;
			break;
		}
	}
	if (all_zeros) {
	} else {
	}
	free(c1);

	char* r1 = (char*)malloc(10);
	if (r1 == NULL) {
		return 1;
	}
	strcpy(r1, "testing");
	char* r2 = (char*)realloc(r1, 20);
	if (r2 == NULL) {
		free(r1);
		return 1;
	}
	if (strcmp(r2, "testing") == 0) {
	} else {
	}
	free(r2);

	int* r3 = (int*)malloc(10 * sizeof(int));
	if (r3 == NULL) {
		return 1;
	}
	for (int i = 0; i < 10; i++) r3[i] = i;

	int* r4 = (int*)realloc(r3, 5 * sizeof(int));
	if (r4 != r3) {
	} else {
	}

	int smaller_content_ok = 1;
	for (int i = 0; i < 5; i++) {
		if (r4[i] != i) {
			smaller_content_ok = 0;
			break;
		}
	}
	if (smaller_content_ok) {
	} else {
	}

	free(r4);

	return 0;
}
