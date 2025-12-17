#include <stdio.h>

int main()
{
    float a = 3.69;
    char *j;
    j = (char *)&a;
    // printf("%d\n", *j);
    for (int i = 0; i < sizeof(float); i++)
    {
        printf("Byte %d: %d\n", i, j[i]);
    }
    printf("Memory representation of float 3.14:\n");
    for (int i = 0; i < sizeof(float); i++)
    {
        printf("Byte %d: 0x%02x\n", i, (unsigned char)j[i]);
    }
    return 0;
}