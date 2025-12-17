/*
	Program: Tic-Tac-Toe Game
	Description: A simple console-based Tic-Tac-Toe game where a player competes against the computer.
	The player marks 'X' and the computer marks 'O'. The game ends when either player wins or it's a draw.
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intro() {
	printf("Welcome to Tic-Tac-Toe!\n");
	printf("You are 'X' and the computer is 'O'.\n");
	printf("The goal is to get three in a row - horizontally, vertically, or diagonally.\n");
	printf("Enter a number (1-9) to place your mark on the board.\n");
}

void setposition(char board[]) {
	char k = '1';
	for (int j = 0; j < 9; j++) {
		board[j] = k;
		k++;
	}
}

void printboard(char set[]) {
	printf(" %c | %c | %c\n", set[0], set[1], set[2]);
	printf("-----------\n");
	printf(" %c | %c | %c\n", set[3], set[4], set[5]);
	printf("-----------\n");
	printf(" %c | %c | %c\n", set[6], set[7], set[8]);
}

void usermove(char play[]) {
	int move, k = 0;
	printboard(play);
	while (k < 100) {
		printf("Make Your Move: ");
		scanf("%d", &move);
		if (move > 0 && move < 10 && isdigit(play[move - 1])) {
			play[move - 1] = 'X';
			break;
		}
		k++;
	}
}

bool complete(char final[]) {
	for (int i = 0; i < 9; i++) {
		if (isdigit(final[i]))
			return false;
	}
	return true;
}

void computermove(char play[]) {
	int r;
	while (1) {
		r = rand() % 9;
		if (isdigit(play[r])) {
			play[r] = 'O';
			break;
		}
	}
}

bool conditions(char win[], int *ch) {
	for (int i = 0; i < 3; i++) {
		if (win[i] == win[i + 3] && win[i + 3] == win[i + 6]) {
			*ch = i;
			return true;
		}
	}

	for (int j = 0; j < 9; j += 3) {
		if (win[j] == win[j + 1] && win[j + 1] == win[j + 2]) {
			*ch = j;
			return true;
		}
	}

	if (win[0] == win[4] && win[4] == win[8]) {
		*ch = 0;
		return true;
	}
	if (win[2] == win[4] && win[4] == win[6]) {
		*ch = 2;
		return true;
	}
	return false;
}

void game() {
	char position[9];
	int index;
	setposition(position);

	while (1) {
		system("cls");
		intro();
		usermove(position);
		if (conditions(position, &index)) {
			if (position[index] == 'X') {
				system("cls");
				intro();
				printboard(position);
				printf("You Won!\n");
				break;
			}
		}
		if (complete(position)) {
			system("cls");
			intro();
			printboard(position);
			printf("Draw!\n");
			break;
		}
		computermove(position);
		if (conditions(position, &index)) {
			if (position[index] == 'O') {
				system("cls");
				intro();
				printboard(position);
				printf("Computer Won!\n");
				break;
			}
		}
		if (complete(position)) {
			system("cls");
			intro();
			printboard(position);
			printf("Draw!\n");
			break;
		}
	}
	printf("Thanks for playing the game");
}

int main() {
	srand(time(0));
	game();
	return 0;
}
