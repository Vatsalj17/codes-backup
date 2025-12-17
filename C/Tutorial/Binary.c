#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimal_to_binary()
{
    int decimal, count = 0;
    int *bits = (int *)calloc(32, sizeof(int));
    printf("Enter a number: ");
    scanf("%d", &decimal);
    int temp = decimal;
    if (decimal < 0)
        decimal = ~(decimal);
    while (decimal != 0)
    {
        bits[count++] = decimal & 1;
        decimal = decimal >> 1;
    }
    if (temp < 0)
    {
        for (int b = 0; b < 32; b++)
        {
            bits[b] = !bits[b];
        }
    }
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", bits[i]);
    }
    free(bits);
}

void binary_to_decimal()
{
    int decimal = 0, i = 31, c = 1;
    char input[32];
    int *binary = (int *)calloc(32, sizeof(int));
    fflush(stdin);
    printf("Enter the binary digits: ");
    while (i >= 0)
    {
        scanf("%c", &input[i]);
        if (input[i] == '\n')
            break;
        if (input[i] != '0' && input[i] != '1')
        {
            printf("Invalid Input");
            free(binary);
            return;
        }
        input[i - 1] = input[i];
        i--;
    }
    for (int j = 31; j > i; j--)
    {
        if (input[j] == '1')
            binary[j] = 1;
        else
            binary[j] = 0;
    }
    for (int k = 31; k >= 0; k--)
    {
        decimal += (binary[k] * c);
        c *= 2;
    }
    printf("%d", decimal);
    free(binary);
}

int main(void)
{
    int selection;
    printf("Select:\n1. Convert Binary to Decimal\n2. Convert Decimal to Binary\n=> ");
    scanf("%d", &selection);
    if (selection == 1)
        binary_to_decimal();
    else if (selection == 2)
        decimal_to_binary();
    else
        printf("Invalid Input");
}
