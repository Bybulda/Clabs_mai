#include <stdio.h>
#include "math.h"
#include "string.h"


int toi(char *s)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = (n * 10) + (s[i] - '0');
    return n;
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
    return;
}


void ifcommon(int n){
    double step = pow(n, 0.5) + 1;
    for (int i = 2; i < (int) step; i+=2){
        if (!(n%i)){
            printf("Yeah, this one is composite number\n");
        }
    }
    printf("This is a common number\n");
}


void split(int n, int del){
    if (del == 0){
        return;
    }
    else if (n / (del* 10) == 0){
        printf("%d ", n / del);
        split(n % del, del / 10);
    }

    else{
        split(n, del*10);
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
    if (n == 1){
        return 1;
    }
    return n + sum(n - 1);
}


long long fact(long long num){
    if (num == 1){
        return num;
    }
    return num * fact(num - 1);
}


int main(int argc, char *argv[]) {
    int n;
    if (argc<3){
        printf("U must enter a number and a flag!\nExample: <number> </p or -p>\n");
    }
    else if (argc == 3 && (!strcmp(argv[2], "-h") || !strcmp(argv[2], "/h"))){
        n = toi(argv[1]);
        kratn(n);
    }
    else if (argc == 3 && (!strcmp(argv[2], "-p") || !strcmp(argv[2], "/p"))){
        ifcommon(toi(argv[1]));
    }
    else if (argc == 3 && (!strcmp(argv[2], "-s") || !strcmp(argv[2], "/s"))){
        split(toi(argv[1]), 1);
    }
    else if (argc == 3 && (!strcmp(argv[2], "-e") || !strcmp(argv[2], "/e"))){
        powers(toi(argv[1]));
    }
    else if (argc == 3 && (!strcmp(argv[2], "-a") || !strcmp(argv[2], "/a"))){
        printf("The sum is %d", sum(toi(argv[1])));
    }
    else if (argc == 3 && (!strcmp(argv[2], "-f") || !strcmp(argv[2], "/f"))){
        printf("The factorial is %lld", fact(toi(argv[1])));
    }
    return 0;
}
