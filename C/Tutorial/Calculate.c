#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *door = (int *)calloc(100, sizeof(int));
    for (int m = 1; m <= 100; m++)
    {
        for (int d = 1; d <= 100; d++)
        {
            if (d >= m)
            {
                if (d % m == 0)
                {
                    if (door[d - 1] == 0)
                        door[d - 1] = 1;
                    else if (door[d - 1] == 1)
                        door[d - 1] = 0;
                }
            }
        }
    }
    for (int o = 0; o < 100; o++)
    {
        if (door[o] == 1)
            printf("%d ", o + 1);
    }
    return 0;
}