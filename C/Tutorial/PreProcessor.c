#include <stdio.h>

#define WINDOWS 1

#ifdef WINDOWS
#define OS "Windows"
#elif defined(LINUX)
#define OS "Linux"
#else
#define OS "Unknown OS"
#endif

int main()
{
    printf("Operating System: %s\n", OS);
    return 0;
}
