#include <stdio.h>
#include <string.h>

int main(void) {
	char *home = "/home/Vatsal";
	char path[64] = "/home/Vatsal/Codes/C";
    size_t psize = strlen(path);
	char *path2 = "/home";
	// char *find = strstr(haystack, needle);
	// if (find == NULL)
	// 	printf("Not found");
	// else
	// 	printf("%s", find);
    if (strstr(path, home) != NULL && psize > strlen(home)) {
        int index = 0;
        for (int i = 0; i < psize; i++) {
            if (home[i] != path[i])
                break;
            index++;
        }
        char npath[64] = {0};
        for (int i = 0; path[index] != '\0'; i++) {
            npath[i] = path[index];
            index++;
        }
        snprintf(path, 64, "~%s", npath);
    }
    printf("%s", path);
}
