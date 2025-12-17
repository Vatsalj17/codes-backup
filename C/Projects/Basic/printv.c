#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void int_to_str(int num, char *buf) {
	char snum[64];
	int digits = 0;
	int n = num;
	int i = 1;
	while (n != 0) {
		n /= 10;
		digits++;
	}
	if (num >= 0) {
		snum[digits] = '\0';
		while (i <= digits) {
			int r = num % 10;
			snum[digits - i] = '0' + r;
			num /= 10;
			i++;
		}
		strcat(buf, snum);
	} else {
		snum[0] = '-';
		snum[digits + 1] = '\0';
		while (i <= digits) {
			int r = num % 10;
			snum[digits - i + 1] = '0' + abs(r);
			num /= 10;
			i++;
		}
		strcat(buf, snum);
	}
}

void float_to_str(float num, char *buf) {
	char fnum[64];
	gcvt(num, 4, fnum);
	// int n = num;
	// int_to_str(n, buf);
	// fnum[0] = '.';
	// float fr = num - n;
	// int i = 1;
	// while (fr != 0) {
	//     int r = fr * 10;
	//     fr = fr*10 -r;
	//     fnum[i] = r;
	//     i++;
	// }
	// fnum[i] = '\0';
	strcat(buf, fnum);
}

void char_to_str(char c, char *buf) {
	char ch[2];
	ch[0] = c;
	ch[1] = '\0';
	strcat(buf, ch);
}

void printv(char *str, ...) {
	int n = strlen(str);
	char buf[1024] = {0};
	va_list list;
	va_start(list, str);
	for (int i = 0; i < n; i++) {
		if (str[i] == '%') {
			switch (str[i + 1]) {
				case 'd': {
					int dtemp = va_arg(list, int);
					int_to_str(dtemp, buf);
					break;
				}
				case 'f': {
					float ftemp = va_arg(list, double);
					float_to_str(ftemp, buf);
					break;
				}
				case 'c': {
					char ctemp = va_arg(list, int);
					char_to_str(ctemp, buf);
					break;
				}
				case 's': {
					char *stemp = va_arg(list, char *);
					strcat(buf, stemp);
					break;
				}
                case '%': {
                    char_to_str('%', buf);
                    break;
                }
				default: {
					i--;
				}
			}
			i++;
		} else {
			char_to_str(str[i], buf);
		}
	}
	write(1, buf, strlen(buf));
	va_end(list);
}

int main(void) {
	int s = 6;
	int k = 78;
	int sum = 4;
	char *str = "hi";
	char c = 'c';
	printv("2 + 2 = %d\n", 4 + 4);
	printv("%d%d %d ha ha %d xd\n", 45, s, 9034, -69);
	printv("%f s f %f\n", 55.6, 77.984);
	printv("%s is string \n%c is char & %% this is just a percent %ha", str, c);
}
