#include <stdio.h>
#include "string.h"
#include "math.h"
#include "limits.h"
#include "stdlib.h"


int toi(char *s){
    int n = 0;
    if (*s == '-'){
        printf("Only positive numbers!!\n");
        exit(0);
    }
    for(int i = 0; s[i] != '\0'; i++){
        if (n > UINT_MAX/10){
            printf("Overflow error, try lower number\n");
            exit(0);
        }
        if (s[i] - '0' < 0 || s[i] - '9' > 9){
            printf("Not a number\n");
            exit(0);
        }
        n = n * 10 + (s[i] - '0');
    }
    if (n == 0){
        printf("Only positive numbers!!\n");
        exit(0);
    }
    return n;
}


void kratn(unsigned int n){
    int flag = 0;
    for (unsigned int i = n; i <= 100; i++){
        if (!(i%n)){
            flag = 1;
            printf("%d ", i);
        }
    }
    if (!flag){
        printf("There were nothing to find");
    }
}


void ifcommon(unsigned int n){
    if (n == 1){
        printf("Thats not a composite and not a common number\n");
        exit(0);
    }
    double step = sqrt(n) + 1;
    for (int i = 2; i < (int) step; i+=2){
        if (!(n%i)){
            printf("Yeah, this one is composite number\n");
        }
    }
    printf("This is a common number\n");
}


void split(unsigned int n){
    if (n != 0){
        split(n / 10);
        printf("%d ", n % 10);
    }
}


void powers(unsigned int n){
    unsigned int tmp;
    for (int i = 1; i < 11; i++){
        printf("For %d: ", i);
        tmp = 1;
        for (int j = 0; j < n; j++){
            if (i > 8 && j > 8){
                printf("%llu ", (unsigned long long) (tmp*=(i)));
            }
            else {
                printf("%d ", tmp*=(i));
            }
        }
        printf("\n");
    }
}


int sum(int n){
    if (n > (UINT_MAX*2)/n - 1){
        printf("Overflow error!\n");
        exit(0);
    }
    return n*(1 + n)/2;
}


unsigned long long fact(unsigned int num){
    if (num == 1){
        return num;
    }
    else if (num > 22){
        printf("OVERFLOW, PLS ENTER SMTH LOWER\n");
        exit(0);
    }
    return num * fact(num - 1);
}


int main(int argc, char *argv[]) {
    int n;
    if (argc!=3){
        printf("U must enter a number and a flag!\nExample: <number> </p or -p>\n");
        exit(0);
    }
    n = toi(argv[1]);
    if (!strcmp(argv[2], "-h") || !strcmp(argv[2], "/h")){
        if (n > 100){
            printf("Enter different number, which is lower than 100\n");
            exit(0);
        }
        kratn(n);
    }
    else if (!strcmp(argv[2], "-p") || !strcmp(argv[2], "/p")){
        ifcommon(n);
    }
    else if (!strcmp(argv[2], "-s") || !strcmp(argv[2], "/s")){
        split(n);
    }
    else if (!strcmp(argv[2], "-e") || !strcmp(argv[2], "/e")){
        if (n > 10){
            printf("Number must be 10 or lower!!\n");
            exit(0);
        }
        powers(n);
    }
    else if (!strcmp(argv[2], "-a") || !strcmp(argv[2], "/a")){
        printf("The sum is %d", sum(n));
    }
    else if (!strcmp(argv[2], "-f") || !strcmp(argv[2], "/f")){
        printf("The factorial is %lld", fact(n));
    }
    return 0;
}
