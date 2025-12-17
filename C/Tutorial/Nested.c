# include<stdio.h>

int main () {
    int n;
    int in=0;
    printf("Enter a number to check if it's prime or not : ");
    scanf("%d", &n);
    for(int i=2;i<=n/2;i++){
        if(n%i == 0){
            in++;
            break;
        }
    }
    if(n<=1){
        printf("invalid input \n");
    }    
    else if (in==0){
        printf("%d is a prime number \n", n);
    } 
    else {
        printf("%d is not a prime number \n", n);
    }
    return 0;
}