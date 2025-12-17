#include <stdio.h>
#include <string.h>

void printstring(char arr[]);
int countstring(char arr[]);
void salting(char arr[]);
void slice(char arr[], int a, int b);
void charcheck(char arr[], char c);
void casechanger(char arr[]);
char highestfrequency(char arr[]);
void spaceremover(char arr[]);
int wordscounter(char arr[]);

int main() {
	char name[51];
	char password[100];

	// char name[]= {'V','A','T','S','A','L','\0'};
	// char surname[]= "JAISWAL";

	printf("Enter your name: ");
	fgets(name, 51, stdin);

	// scanf("%s", &name);
	// printstring(name);

	printf("Enter a password: ");
	fgets(password, 100, stdin);
	printf("Welcome! %s to my program\n", name);
	printf("Your name contains %d letters\n", countstring(name));

	// printf("Your name contains %d letters\n", strlen(name));

	salting(password);
	printf("Salted version of your password is: \n");
	puts(password);

	casechanger(password);
	printf("New suggested password(LOL XD): ");
	puts(password);

	int m, n;
	printf("Initial Slicer: ");
	scanf("%d", &m);
	printf("Final Slicer: ");
	scanf("%d", &n);
	slice(name, m, n);

	char ch;
	printf("Enter a letter to check it's presence in your name: ");
	fflush(stdin);
	scanf("%c", &ch);
	charcheck(name, ch);

	spaceremover(name);
	printf("Your name without blank spaces is: ");
	puts(name);

	char sentence[100];
	printf("Enter a sentence: ");
	fgets(sentence, 100, stdin);
	printf("%c is the maximum occuring letter\n", highestfrequency(sentence));
	printf("No. of words in this sentence are %d\n", wordscounter(sentence));

	return 0;
}

void printstring(char arr[]) {
	for (int i = 0; arr[i] != '\0'; i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}

int countstring(char arr[]) {
	int t = 0;
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == ' ') {
			continue;  // t--;
		}
		t++;
	}
	return t;
}

void salting(char arr[]) {
	char salt[] = "123";
	strcat(arr, salt);
}

void slice(char arr[], int a, int b) {
	if (a >= 0 && b <= strlen(arr) && b >= a) {
		for (int i = a; i <= b; i++) {
			printf("%c", arr[i]);
		}
	} else {
		printf("Invalid input for slice");
	}
	printf("\n");
}

void charcheck(char arr[], char c) {
	int chk = 0;
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == c) {
			chk++;
		}
	}
	if (chk == 0) {
		printf("%c is NOT present in your name\n", c);
	} else {
		printf("%c is present in your name\n", c);
	}
}

void casechanger(char arr[]) {
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] >= 65 && arr[i] <= 90) {
			arr[i] = arr[i] + 32;
		} else if (arr[i] >= 97 && arr[i] <= 122) {
			arr[i] = arr[i] - 32;
		}
	}
}

char highestfrequency(char arr[]) {
	// int frequncy[256] = {0};
	char max;
	int highest = 0;
	int count = 0;
	for (int i = 'A'; i <= 'z'; i++) {
		for (int j = 0; arr[j] != '\0'; j++) {
			if (i == arr[j]) {
				count++;
			}
		}
		if (count > highest) {
			highest = count;
			max = i;
		}
	}
	return max;
}

void spaceremover(char arr[]) {
	// char newarr[];
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == ' ') {
			for (int j = i; arr[j] != '\0'; j++) {
				arr[j] = arr[j + 1];
			}
		}
	}
}

int wordscounter(char arr[]) {
	int wcount = 1;
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == ' ') {
			// while (arr[i] == ' ')
			// {
			//     i++;
			// }
			wcount++;
		}
	}
	return wcount;
}
