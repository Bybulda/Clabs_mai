#include <stdio.h>
#include "math.h"

int sum(int n){
    if (n == 1){
        return 1;
    }
    return n + sum(n - 1);
}

int common(int n){
    return 0;
}

int split(int n, int del){
    if (del == 0){
        return 0;
    }
    else if (n / (del* 10) == 0){
        printf("%d ", n / del);
        split(n % del, del / 10);
    }

    else{
        split(n, del*10);
    }

}



unsigned fact(unsigned int num){
    if (num == 1){
        return num;
    }
    return num * fact(num - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    int b = sum(n);
    printf("%d\n", b);
    return 0;
}
