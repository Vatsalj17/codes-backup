#include <stdio.h>

int digisum(int n, int o);
int digicounter(int h);
int power(int a,int b);
int sqroot(int r);

int main() {
    int m;
    printf("Enter a number: ");
    scanf("%d", &m);
    int nd = digicounter(m);
    int sum = digisum(nd, m);
    int root = sqroot(m);
    printf("No. of digits = %d\n", nd);
    printf("Sum of digits of the number = %d\n", sum);
    if (root!=1234) {
        printf("Root is %d\n", root);
    } else {
        printf("Not a perfect square\n");
    }
    
    return 0;
}

int digisum(int n, int o) {
    int j=0;
    int s;
    for(int i = power(10,n); i>=1; i=i/10) {
        s=o/i;
        j=j+s;
        o=o-(s*i);
    }
    return j;
}

int digicounter(int h) {
    int p = 10;
    int q = 1;
    while(p<=h) {
        int s = h/p;
        if (s==0) {
            break;
        }
        p=p*10;
        q++;
    }
    return q;
}

int power(int a,int b) {
    int c =1;
    for(int i=1;i<=b;i++) {
        c=c*a; 
    }
    return c;
}

int sqroot(int r){
    int t;
    int i=1;
    int j=1234;
    while(i<=1000){
        t=i*i;
        if (t==r) {
            break;
        }
        i++;
    }
    if(i<=1000) {
        return i;
    } else {
        return j;
    }
}
