#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(0));
	int r = rand();
	printf("Welcome to the 'NUMBER GUESSING GAME'\n");
	printf("You have to guess the random number chosen by me\n");
	printf("Let's Start\n");
	int i = 1;
	while (i <= 100) {
		int n;
		printf("Guess it: ");
		scanf("%d", &n);
		if (n < r) {
			printf("Higher\n");
		} else if (n > r) {
			printf("Lower\n");
		} else if (n == r) {
			break;
		}
		i++;
	}
	printf("Congratulations! You guessed it.\n");
	printf("Total guesses: %d\n", i);
	return 0;
}
