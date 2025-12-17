#include<stdio.h>

void pattern(int a);
void reverse(int a);
int digi_counter(int a);
void count_p_c();

int main(void) {
    // int n;
    // scanf("%d", &n);
    count_p_c();
}

void pattern(int a) {
    for(int i = 1; i <= a; i++) {
        for(int k = 0; k < a-i;k++) {
            printf(" ");
        }
        for(int j = 1; j < i; j++) {
            printf("%d", j);
        } 
        printf("%d", i);
        for(int l = i-1; l > 0; l--) {
            printf("%d", l);
        }
        printf("\n");
    }
}

int digi_counter(int a) {
    int count = 0;
    int s=a;
    for(int i = 10;s != 0; i = i*10) {
        s = a/i;
        count++;
    }
    return count;
}

void reverse(int a) {
    int new_num;
    while(a != 0) {
        new_num = a % 10;
        printf("%d", new_num);
        a = a / 10;
    }
    printf("\n");
}

void count_p_c() {
    int n;
    int check_p = 0, check_c = 0;
    do {
        printf("Enter a number: ");
        scanf("%d", &n);
        if(n == -1) {
            continue;
        }
        int check = 0;
        for (int i = 2; i <= n/2; i++) {
            if (n % i == 0) {
                check++;
            }
        }
        if (check == 0) {
            check_p++;
        } else {
            check_c++;
        }
    } while (n != -1);
    printf("No. of prime numbers = %d\n", check_p);
    printf("No. of composite number = %d\n", check_c);
} 
