/*
	Program: Tic-Tac-Toe Game
	Description: A simple console-based Tic-Tac-Toe game where a player competes against the computer.
	The player can choose a difficulty level and their symbol ('X' or 'O') alternates between games.
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Forward declarations
void easy_computermove(char play[], char computer_char);
void medium_computermove(char play[], char computer_char, char player_char);
void hard_computermove(char play[], char computer_char, char player_char);
void computermove(char play[], int difficulty, char computer_char, char player_char);
bool conditions(char win[], int *ch);

void intro(char player_char, char computer_char) {
	printf("Welcome to Tic-Tac-Toe!\n");
	printf("You are '%c' and the computer is '%c'.\n", player_char, computer_char);
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
	printf("\n");
	printf(" %c | %c | %c\n", set[0], set[1], set[2]);
	printf("-----------\n");
	printf(" %c | %c | %c\n", set[3], set[4], set[5]);
	printf("-----------\n");
	printf(" %c | %c | %c\n", set[6], set[7], set[8]);
	printf("\n");
}

void usermove(char play[], char player_char) {
	int move;
	while (1) {
		printf("Make Your Move (1-9): ");
		if (scanf("%d", &move) != 1) {
			// Clear input buffer
			while (getchar() != '\n');
			printf("Invalid input. Please enter a number.\n");
			continue;
		}

		if (move > 0 && move < 10 && isdigit(play[move - 1])) {
			play[move - 1] = player_char;
			break;
		} else {
			printf("Invalid move. That spot is taken or out of bounds. Try again.\n");
		}
	}
}

bool complete(char final[]) {
	for (int i = 0; i < 9; i++) {
		if (isdigit(final[i]))
			return false;
	}
	return true;
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

void easy_computermove(char play[], char computer_char) {
	int r;
	while (1) {
		r = rand() % 9;
		if (isdigit(play[r])) {
			play[r] = computer_char;
			break;
		}
	}
}

// Helper function to check for a winning or blocking move
int find_winning_or_blocking_move(char play[], char mark) {
	for (int i = 0; i < 9; i++) {
		if (isdigit(play[i])) {
			char original_char = play[i];
			play[i] = mark;
			int dummy;
			if (conditions(play, &dummy)) {
				play[i] = original_char;  // revert
				return i;
			}
			play[i] = original_char;  // revert
		}
	}
	return -1;
}

void medium_computermove(char play[], char computer_char, char player_char) {
	// 1. Check if computer can win
	int move = find_winning_or_blocking_move(play, computer_char);
	if (move != -1) {
		play[move] = computer_char;
		return;
	}

	// 2. Check if player can win, and block them
	move = find_winning_or_blocking_move(play, player_char);
	if (move != -1) {
		play[move] = computer_char;
		return;
	}

	// 3. Otherwise, make a random move
	easy_computermove(play, computer_char);
}

void hard_computermove(char play[], char computer_char, char player_char) {
	// 1. Check if computer can win
	int move = find_winning_or_blocking_move(play, computer_char);
	if (move != -1) {
		play[move] = computer_char;
		return;
	}

	// 2. Check if player can win, and block them
	move = find_winning_or_blocking_move(play, player_char);
	if (move != -1) {
		play[move] = computer_char;
		return;
	}

	// 3. Take center if available
	if (isdigit(play[4])) {
		play[4] = computer_char;
		return;
	}

	// 4. Take an available corner
	int corners[] = {0, 2, 6, 8};
	int available_corners[4];
	int num_available = 0;
	for (int i = 0; i < 4; i++) {
		if (isdigit(play[corners[i]])) {
			available_corners[num_available++] = corners[i];
		}
	}
	if (num_available > 0) {
		play[available_corners[rand() % num_available]] = computer_char;
		return;
	}

	// 5. Take an available side
	int sides[] = {1, 3, 5, 7};
	int available_sides[4];
	num_available = 0;
	for (int i = 0; i < 4; i++) {
		if (isdigit(play[sides[i]])) {
			available_sides[num_available++] = sides[i];
		}
	}
	if (num_available > 0) {
		play[available_sides[rand() % num_available]] = computer_char;
		return;
	}

	// 6. Fallback if no strategic spot is available
	easy_computermove(play, computer_char);
}

void computermove(char play[], int difficulty, char computer_char, char player_char) {
	switch (difficulty) {
		case 1:
			easy_computermove(play, computer_char);
			break;
		case 2:
			medium_computermove(play, computer_char, player_char);
			break;
		case 3:
			hard_computermove(play, computer_char, player_char);
			break;
		default:
			easy_computermove(play, computer_char);	 // Fallback
			break;
	}
}

void game(int difficulty, char player_char, char computer_char) {
	char position[9];
	int index;
	setposition(position);

	// 'X' always starts the game
	char current_turn_char = 'X';

	while (1) {
		system("clear || cls");
		intro(player_char, computer_char);
		printboard(position);

		if (current_turn_char == player_char) {
			usermove(position, player_char);
		} else {
			printf("Computer is thinking...\n");
			computermove(position, difficulty, computer_char, player_char);
		}

		if (conditions(position, &index)) {
			system("clear || cls");
			intro(player_char, computer_char);
			printboard(position);
			if (position[index] == player_char) {
				printf("You Won!\n");
			} else {
				printf("Computer Won!\n");
			}
			break;
		}

		if (complete(position)) {
			system("clear || cls");
			intro(player_char, computer_char);
			printboard(position);
			printf("Draw!\n");
			break;
		}

		// Switch turns
		current_turn_char = (current_turn_char == 'X') ? 'O' : 'X';
	}
	printf("\nThanks for playing!\n");
}

int main() {
	srand(time(0));
	int difficulty = 1;
	char player_char = 'X';
	char computer_char = 'O';
	char play_again;

	do {
		system("clear || cls");
		printf("Welcome to Tic-Tac-Toe!\n");
		printf("Choose difficulty:\n");
		printf("1. Easy\n");
		printf("2. Medium\n");
		printf("3. Hard\n");
		printf("Enter choice (1-3): ");

		if (scanf("%d", &difficulty) != 1) {
			// Clear input buffer
			while (getchar() != '\n');
			difficulty = 1;	 // Default
		}

		if (difficulty < 1 || difficulty > 3) {
			printf("Invalid choice, defaulting to Easy.\n");
			difficulty = 1;
		}

		game(difficulty, player_char, computer_char);

		printf("\nPlay again? (y/n): ");
		scanf(" %c", &play_again);

		// Swap symbols for the next game
		if (play_again == 'y' || play_again == 'Y') {
			char temp = player_char;
			player_char = computer_char;
			computer_char = temp;
		}

	} while (play_again == 'y' || play_again == 'Y');

	printf("Goodbye!\n");

	return 0;
}
