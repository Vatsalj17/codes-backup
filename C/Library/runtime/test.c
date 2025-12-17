#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("usage: %s <library> <number>\n", argv[0]);
		exit(1);
	}
	char* librarypath = argv[1];
	int number = atoi(argv[2]);
	void* libhandle = dlopen(librarypath, RTLD_LAZY);
	if (libhandle == NULL) {
		perror("dlopen");
        return EXIT_FAILURE;
	}
    int (*opfunc) (int);
    char* (*name) ();
    if ((opfunc = dlsym(libhandle, "do_operation")) == NULL) {
        perror("do_operation");
        return EXIT_FAILURE;
    }
    if ((name = dlsym(libhandle, "get_library_name")) == NULL) {
        perror("get_library_name");
        return EXIT_FAILURE;
    }
    printf("Library name: %s\n", name());
    printf("%d -> %d\n", number, opfunc(number));
    dlclose(libhandle);
    return EXIT_SUCCESS;
}
