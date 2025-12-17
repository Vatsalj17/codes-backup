#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
	// reset to original state
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios;
    /*
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    */

	// Input flags - clear these bits to disable input processing features
	raw.c_iflag &= ~(BRKINT	  // Disable SIGINT on break condition
		| ICRNL	  // Disable translation of carriage return '\r' to newline '\n'
		| INPCK	  // Disable parity checking
		| ISTRIP  // Disable stripping off the 8th bit (i.e., preserve all 8 bits of input)
		| IXON);  // Disable software flow control (Ctrl-S / Ctrl-Q)

	// Output flags - clear post-processing of output
	raw.c_oflag &= ~(OPOST);  // Disable all output processing (e.g., no automatic newline translation)

	// Control flags - set character size to 8 bits per byte
	raw.c_cflag |= (CS8);  // Set 8-bit characters (no parity)

	// Local flags - clear these bits to disable canonical mode and various signals/features
	raw.c_lflag &= ~(ECHO  // Disable echoing typed characters to the terminal
					 | ICANON  // Disable canonical mode (read input byte-by-byte instead of line-by-line)
					 | IEXTEN  // Disable implementation-defined input processing (e.g., Ctrl-V)
					 | ISIG);  // Disable generating signals like SIGINT (Ctrl-C), SIGTSTP (Ctrl-Z)

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
	enableRawMode();
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
	}
	return 0;
}
