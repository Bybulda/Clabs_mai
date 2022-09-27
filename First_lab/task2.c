#include <stdio.h>
#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define EPS 1e-7


float tof(char *s){
    float res = 0;
    int afterdot = 0;
    float stepen = 1;
    int neg = 0;
    if (*s == '-'){
        s++;
        neg = 1;
    }
    while (*s){
        if (afterdot){
            stepen = stepen / 10;
            res = res + (*s - '0') * stepen;
        }
        else{
            if (*s == '.' || *s == ',')
                afterdot++;
            else
                res = res * 10.0 + (*s - '0');
        }
        s++;
    }
    if(neg) return -res;
    else    return  res;
}

int checker(double d){
    if (d < EPS){
        return 0;
    }
    return 1;
}

double find_x_d(double b, double a, double d){
    return (b+d) / (2*a);
}


double f_x(float a, float b, float c){
    float arr[3] = {a, b, c};
    double disc = 0;
    for (int i = 0; i < 3; i++){
        a = arr[i];
        b = arr[(i+1)%3];
        c = arr[(i+2)%3];
        disc = b * b - 4 * a*c;
        if (checker(disc) && checker(arr[i])){
            disc = sqrt(disc);
            printf("The answer for %lf*x^2 + %lf*x + %lf = 0 is x1 = %lf, x2 = %lf\n", a, b, c, find_x_d(b, a, disc), find_x_d(b, a, -disc));
        }
        else{
            printf("The equation %lf*x^2 + %lf*x + %lf = 0 has no roots\n", a, b, c);
        }
        disc = c * c - 4 * a*b;
        if (checker(disc) && arr[i] != 0){
            disc = sqrt(disc);
            printf("The answer for %lf*x^2 + %lf*x + %lf = 0 is x1 = %lf, x2 = %lf\n", a, c, b, find_x_d(c, a, disc), find_x_d(c, a, -disc));
        }
        else{
            printf("The equation %lf*x^2 + %lf*x + %lf = 0 has no roots\n", a, c, b);
        }
    }
}


int kratn(float a, float b){
    if (checker(a) && checker(b))
        return (int) a& (int) b;
    else
        return -1;
}


int if_triangle(double a, double b, double c) {
    if (!checker(a) && !checker(b) && !checker(c))
        printf("Please use natural numbers!\n");
    a *= a;
    b *= b;
    c *= c;
    if (!checker(a + b - c) || !checker(a + c - b) || !checker(b + c - a)){
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int n;
    if (argc<4){
        printf("U must enter a number and a flag!\nExample: <flag> </q or -q> <number>\n");
    }
    else if (argc == 5 && (!strcmp(argv[1], "-q") || !strcmp(argv[1], "/q"))){
        f_x(tof(argv[2]), tof(argv[3]), tof(argv[4]));
    }
    else if (argc == 4 && (!strcmp(argv[1], "-m") || !strcmp(argv[1], "/m"))){
        float a = tof(argv[2]);
        float b = tof(argv[3]);
        int res = kratn(a, b);
        if (res == -1)
            printf("Smth went wrong, please use natural numbers\n");
        else
            printf("Yes %lf is a multiple of %lf\n", a, b);
    }
    else if (argc == 5 && (!strcmp(argv[1], "-t") || !strcmp(argv[1], "/t"))){
        int res = if_triangle(tof(argv[2]), tof(argv[3]), tof(argv[4]));
        res ? printf("Yes it can be a right triangle\n") : printf("No it cant be a right triangle\n");
    }
    else{
        printf("Something went wrong, try again pls\n");
    }
    return 0;
}
