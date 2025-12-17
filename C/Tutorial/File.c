#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct sinfo
{
    char name[100];
    int age;
    float cgpa;
    char branch[100];
} si;

void studentinfo(si student[], FILE *f)
{
    printf("Enter your name: ");
    gets(student[1].name);
    printf("Enter your age: ");
    scanf("%d", &student[1].age);
    printf("Enter your cgpa:");
    scanf("%f", &student[1].cgpa);
    fprintf(f, "My name is %s\n", student[1].name);
    fprintf(f, "My age is %d\n", student[1].age);
    fprintf(f, "My cgpa is %f\n", student[1].cgpa);
}

void getfile(char ch, FILE *f)
{
    ch = fgetc(f);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(f);
    }
}

void printoddnumbers(int n, FILE *f)
{
    printf("Enter a number: ");
    scanf("%d", &n);
    fprintf(f, "Odd numbers from 1 to %d are: ", n);
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 != 0)
        {
            fprintf(f, "%d\t", i);
        }
    }
}

int main()
{
    si student[5];
    int o;
    char ch;
    FILE *f;
    f = fopen("io.txt", "a");
    for (int i = 0; i < 3; i++)
    {
        fflush(stdin);
        printf("Enter name of student %d: ", i + 1);
        gets(student[i].name);
        printf("Enter age of student %d: ", i + 1);
        scanf("%d", &student[i].age);
        printf("Enter cgpa of student %d: ", i + 1);
        scanf("%f", &student[i].cgpa);
        fflush(stdin);
        printf("Enter branch of student %d: ", i + 1);
        gets(student[i].branch);
    }
    fprintf(f, "S.No.  Name                 Age  CGPA  Branch\n");
    for (int k = 0; k < 3; k++)
    {
        fprintf(f, "%d      %-20s %d   %.1f   %s\n", k + 1, student[k].name, student[k].age, student[k].cgpa, student[k].branch);
    }

    // printoddnumbers(o, f); //turn the file in either append mode or read mode
    // getfile(ch, f); //turn the file into read mode
    // studentinfo(student, f); //turn the file into append mode

    fclose(f);
    return 0;
}