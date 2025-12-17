#include <stdio.h>
#include <string.h>

struct student
{
    int roll;
    char name[100];
    float cgpa;
};

typedef struct address
{
    int house_no;
    int block;
    char city[100];
    char state[100];
} add;

typedef struct complex
{
    int real;
    int img;
} clx;

void giveadd(add arr[], int a);

int main()
{
    add citizen[5];
    char opt[6];
    for (int i = 0; i < 5; i++)
    {
        printf("Enter respective details for citizen %d\n", i + 1);
        printf("House Number: ");
        scanf("%d", &citizen[i].house_no);
        printf("Block: ");
        scanf("%d", &citizen[i].block);
        printf("City: ");
        scanf("%s", &citizen[i].city);
        printf("State: ");
        // fgets(citizen[i].state, 100, stdin);
        scanf(" %s", &citizen[i].state);
    }
    printf("Thank you for giving your details\n");
    printf("Your data has been stored\n");
    printf("Do you want to know address of any citizen?\n");
    scanf("%s", &opt);
    char Yes[] = "Yes";
    char yes[] = "yes";
    if (strcmp(Yes, opt) == 0 || strcmp(yes, opt) == 0)
    {
        int c;
        printf("Enter the number of the citizen to get it's address: ");
        scanf("%d", &c);
        if (c <= 5 && c >= 1)
        {
            giveadd(citizen, c);
        }
        else
        {
            printf("invalid input");
        }
    }
    else
    {
        printf("Thank you");
    }
    clx no1;
    printf("Enter Real part of the number: ");
    scanf("%d", &no1.real);
    printf("Enter Imaginary part of the number: ");
    scanf("%d", &no1.img);
    clx *n;
    n = &no1;
    printf("The complex number is: %d+%di", n->real, n->img);
    return 0;
}

void giveadd(add arr[], int a)
{
    printf("Address of citizen %d is:\n", a);
    printf("%d %d %s %s\n", arr[a - 1].house_no, arr[a - 1].block, arr[a - 1].city, arr[a - 1].state);
}
