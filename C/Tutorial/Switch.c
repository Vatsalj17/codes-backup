# include<stdio.h>

int main () {
    char grade;
    printf("Enter your grade (A-H): ");
    scanf("%c", &grade);

    switch (grade) {
        case 'A' : printf("very good");
        break;
        case 'B' : printf("good");
        break;
        case 'C' : printf("nice");
        break;
        case 'D' : printf("not bad");
        break;
        case 'E' : printf("bad");
        break;
        case 'F' : printf("poor");
        break;
        case 'G' : printf("very poor");
        break;
        case 'H' : printf("worst");
        break;
        default : printf("not a valid grade");
    }
    return 0;
}