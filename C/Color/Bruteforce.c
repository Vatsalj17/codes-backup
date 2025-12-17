#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void green() { printf("\033[1;32m"); }

void reset() { printf("\033[0m"); }

void sleep_ms(int milliseconds) {
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void move_cursor(int row, int col) { printf("\033[%d;%dH", row, col); }

void hide_cursor() { printf("\033[?25l"); }

void show_cursor() { printf("\033[?25h"); }

int main(void) {
	char str[] = "Hello World!";
	green();
	hide_cursor();
	system("clear");
	for (int i = 0; str[i] != '\0'; i++) {
		for (char j = 32; j <= str[i]; j++) {
			move_cursor(1, i + 1);
			printf("%c", j);
			fflush(stdout);
			sleep_ms(20);
		}
	}
	printf("\n");
	reset();
	show_cursor();
}
