#define _GNU_SOURCE

#include <unistd.h>
#include <dlfcn.h>

/* int rand() {
	return 42;
} */

int rand() {
    int (*orig_rand) (void) = dlsym(RTLD_NEXT, "rand");
    return orig_rand() % 100;
}

// int printf(const char* str, ...) {
// 	write(1, "printf hacked!\n", 15);
// 	return 15;
// }
//
// int puts(const char* str) {
// 	write(1, "puts hacked!\n", 13);
// 	return 13;
// }
