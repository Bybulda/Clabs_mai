#include <stdio.h>
#include "math.h"
#include "string.h"
#include "limits.h"
#include "stdlib.h"
#include "ctype.h"

#define EPS 1e-7


 int toi(char *s){
    int n = 0;
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
    return n;
}


double tof(char *s){
    return 1.9;
}


int int_or_float(char *s){
    int flag = 0;
    while(*s){
        if (!isdigit(*s)){
            if (*s == '.' || *s == ','){
                flag = 1;
                break;
            }
            if (isalpha(*s)) {
                printf("Please use numbers!!\n");
                exit(0);
            }
        }
        *s++;
    }
    if (!flag) return 1;
    else return 0;
}
double find_x(double b, double c){
    return -1. * (c) / b;
}


double find_x_d(int b, double a, double d){
    return ((-sqrt(b))+d) / (2*a);
}


int descrim(int a, int b, int c){
    return b * b - 4 * a * c;
}


void f_x(float a, float b, float c){
    double discr = b * b - 4 * a * c;
    if (fabs(discr) < EPS){
        printf("Zero solvings for this one")
    }
}


void kratn(float a, int b){
    !(a%b) ? printf("Yes, %d kratno %d\n", a, b) : printf("No, %d ne kratno %d\n", a, b);
}


void if_triangle(double a, double b, double c){
    a *= a;
    b *= b;
    c *= c;
    if (a + b == c || a + c == b || b + c == a){
        printf("Yes it can be a right triangle\n");
    }
    else{
        printf("No, it`s not a right triangle\n");
    }
}


int main(int argc, char *argv[]) {
    int n;
//    printf("%d\n", argc);
    if (argc<4){
        printf("U must enter a number and a flag!\nExample: <number> </q or -q>\n");
    }
    else if (argc == 5 && (!strcmp(argv[1], "-q") || !strcmp(argv[1], "/q"))){
        n = toi(argv[1]);
//        kratn(n);
    }
    else if (argc == 4 && (!strcmp(argv[1], "-m") || !strcmp(argv[1], "/m"))){
        if (int_or_float(argv[2]) && int_or_float(argv[3])){
            kratn(toi(argv[2]), toi(argv[3]));
        }
        else{
            printf("You cant use float numbers bro!\n");
            exit(0);
        }

    }
    else if (argc == 5 && (!strcmp(argv[1], "-t") || !strcmp(argv[1], "/t"))){
        if_triangle(toi(argv[2]), toi(argv[3]), toi(argv[4]));
    }
    else{
        printf("Something went wrong, try again pls\n");
    }
    return 0;
}