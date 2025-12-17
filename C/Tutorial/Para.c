#include <stdio.h>

void readapara(char *str);
int no_of_lines(char *str);
void bulletin(char *str);

int main(void)
{
    char para[1000];
    printf("Write your paragraph: \n");
    readapara(para);
    printf("No. of lines in your paragraph = %d\n", no_of_lines(para));
    bulletin(para);
    // puts(para);
}

void readapara(char *str)
{
    int i = 0;
    printf("Put * to stop reading\n");
    do
    {
        scanf("%c", &str[i]);
        i++;
    } while (str[i - 1] != '*');
    str[i] = '\0';
}

int no_of_lines(char *str)
{
    int nlines = 1;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            nlines++;
        }
    }
    return nlines;
}

void bulletin(char *str)
{
    printf("1. ");
    int point = 2;
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
        if (str[i] == '\n')
        {
            printf("%d. ", point);
            point++;
        }
    }
    printf("\n");
}
