/*
Command-Line Calculator with Input Validation in C
*/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function to perform the calculations
float calculation(char *in, float initial, int review) {
	int i = 0, y = (review == 0) ? 0 : 1, x = 0, v = 1;
	float num[50] = {0.00};	 // Array to store numbers
	char operator[50];		 // Array to store operators

	// Extract numbers from the input string
	for (int j = 0; in[j] != '\0'; j++) {
		if (isdigit(in[j])) {
			while (isdigit(in[j])) {
				num[y] = num[y] * 10 + (in[j] - 48);
				j++;
			}
			j--;
			y++;
		}
	}

	// Extract operators from the input string
	for (int k = 0; in[k] != '\0'; k++) {
		if (in[k] == 43 || in[k] == 45 || in[k] == 42 || in[k] == 47 ||
			in[k] == 94) {
			operator[x] = in[k];
			x++;
		}
	}

	// Use previous result if this is not the first calculation
	if (review != 0) num[0] = initial;

	// Perform the calculations based on extracted operators
	float result = num[0];
	for (int z = 0; z <= strlen(in); z++) {
		switch (operator[z]) {
			case 43:
				result += num[v];
				break;
			case 45:
				result -= num[v];
				break;
			case 42:
				result *= num[v];
				break;
			case 47:
				result /= num[v];
				break;
			case 94:
				result = pow(result, num[v]);
				break;
		}
		v++;
	}
	return result;
}

// Function to check validity of the input
bool isvalid(char *in, int review) {
	for (int i = 0; in[i] != '\0'; i++) {
		// Ensure the input only contains valid characters
		if (!(isdigit(in[i]) || in[i] == 43 || in[i] == 45 || in[i] == 42 ||
			  in[i] == 47 || isspace(in[i]) || in[i] == 94))
			return false;

		// Prevent Division by zero
		if (in[i] == 47) {
			int temp = i;
			while (isspace(in[i + 1])) {
				i++;
			}
			if (in[i + 1] == 48) return false;
			i = temp;
		}
	}

	// Check for consecutive operators and invalid placements
	int check = 0;
	for (int j = 0; in[j] != '\0'; j++) {
		if (in[j] == 43 || in[j] == 45 || in[j] == 42 || in[j] == 47 ||
			in[j] == 94) {
			while (!(isdigit(in[j]) || in[j] == '\0')) {
				j++;
				if (in[j] == 43 || in[j] == 45 || in[j] == 42 || in[j] == 47 ||
					in[j] == 94)
					check++;
			}
			j--;
		}
		if (check != 0) return false;  // Consecutive operators found
	}

	// For subsequent calculations, ensure input starts with an operator
	if (review != 0) {
		if (isdigit(in[0]))
			return false;  // Invalid: input starts with a digit instead of an
						   // operator
		else if (isspace(in[0])) {
			int k = 0;
			while (isspace(in[k])) {
				k++;
			}
			if (isdigit(in[k])) return false;
		}
	}
	return true;  // Input is valid
}

// Function to handle input, validation, and calculation results
void calculator() {
	char calc[100];
	float var[100];
	int f = 0;
	printf("Enter your calculations here: \n");
	while (1) {
		fgets(calc, 100, stdin);  // Take user input

		// Exit loop if the user presses Enter without input
		if (strcmp(calc, "\n") == 0) break;

		// Validate input and perform the calculation
		if (isvalid(calc, f)) {
			var[f] = calculation(calc, var[f - 1], f);
			printf("= %.2f\n", var[f]);
			printf("Ans");
			f++;
			fflush(stdin);
		} else {
			printf("Syntax Error");	 // Display error message for invalid input
			break;
		}
	}
}

// Main function to run the calculator
int main() {
	// Calling the Calculator function
	calculator();
	return 0;
}
