#include <stdio.h>
#include "math.h"
#include "string.h"
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


double find_x(double b, double c){
    return -1. * (c*c) / b;
}


double find_x_d(int b, double a, double d){
    return ((-sqrt(b))+d) / (2*a);
}


int descrim(int a, int b, int c){
    return b * b - 4 * a * c;
}


void f_x(int a, int b, int c){
    printf("For a*x^2 + b*x + c^2 = 0\n x1 = %lf, x2 = %lf", a, b);
}


void kratn(int a, int b){
    !(a%b) ? printf("Yes, %d kratno %d\n", a, b) : printf("No, %d ne kratno %d\n", a, b);
}


void if_triangle(int a, int b, int c){
    if ((a + b > c && c > a && c > b) || (a + c > b && b > c && b > a)
    || (c + b > a && a > c && a > b)){
        printf("Yes it can be a triangle\n");
    }
    else{
        printf("No, it`s not a triangle\n");
    }
}


int main(int argc, char *argv[]) {
    int n;
    printf("%d\n", argc);
    if (argc<4){
        printf("U must enter a number and a flag!\nExample: <number> </q or -q>\n");
    }
    else if (argc == 5 && (!strcmp(argv[1], "-q") || !strcmp(argv[1], "/q"))){
        n = toi(argv[1]);
//        kratn(n);
    }
    else if (argc == 4 && (!strcmp(argv[1], "-m") || !strcmp(argv[1], "/m"))){
        kratn(toi(argv[2]), toi(argv[3]));
    }
    else if (argc == 5 && (!strcmp(argv[1], "-t") || !strcmp(argv[1], "/t"))){
        if_triangle(toi(argv[2]), toi(argv[3]), toi(argv[4]));
    }
    else{
        printf("Something went wrong, try again pls\n");
    }
    return 0;
}