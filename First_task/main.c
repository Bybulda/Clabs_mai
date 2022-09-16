#include <stdio.h>
#include "string.h"
#include "math.h"
#include "limits.h"
#include "stdlib.h"


int toi(char *s){
    int n = 0;
    for(int i = 0; s[i] != '\0'; i++){
        if (n > INT_MAX/10){
            printf("Overflow error, try lower number\n");
            exit(0);
        }
        if (s[i] - '0' < 0 || s[i] - '9' > 9){
            printf("Not a number\n");
            exit(0);
        }
        n = n * 10 + (s[i] - '0');
    }
    return n;
}


double power(double a, double n){
    if (n == 1){
        return a;
    }
    return a * power(a, n - 1);
}


void kratn(int n){
    int flag = 0;
    for (int i = n; i <= 100; i++){
        if (!(i%n)){
            flag = 1;
            printf("%d ", i);
        }
    }
    if (!flag){
        printf("There were nothing to find");
    }
}


void ifcommon(int n){
    double step = sqrt(n) + 1;
    for (int i = 2; i < (int) step; i+=2){
        if (!(n%i)){
            printf("Yeah, this one is composite number\n");
        }
    }
    printf("This is a common number\n");
}


void split(int n){
    if (n != 0){
        split(n / 10);
        printf("%d ", n % 10);
    }
}


void powers(int n){
    printf("1 ");
    for (int i = 2; i<=n;i++){
        if (i >9){
            printf("%lld ", (long long) pow(i, i));
        }
        else{
            printf("%d ", (int) pow(i, i));
        }
    }
}


int sum(int n){
    return n*(1 + n)/2;
}


long long fact(long long num){
    if (num == 1){
        return num;
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
        kratn(n);
    }
    else if (!strcmp(argv[2], "-p") || !strcmp(argv[2], "/p")){
        ifcommon(n);
    }
    else if (!strcmp(argv[2], "-s") || !strcmp(argv[2], "/s")){
        split(n);
    }
    else if (!strcmp(argv[2], "-e") || !strcmp(argv[2], "/e")){
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
