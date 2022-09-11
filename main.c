#include <stdio.h>
#include "math.h"


int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = (n * 10) + (s[i] - '0');
    return n;
}

int ifcommon(int n){
    int step = pow(n, 0.5) + 1;
    for (int i = 3; i*i < step; i+=2){
        if (!n%i){
            return 1;
        }
    }
    return 0;
}

int powers(int n){
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

int kratn(int n){
    int flag = 0;
    for (int i = 2; i < 100; i++){
        if (!i%n){
            flag = 1;
            printf("%d ", i);
        }
    }
    if (!flag){
        printf("There were nothing to find");
    }
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
    powers(n);
//    int b = sum(n);
//    printf("%d\n", b);
    return 0;
}
