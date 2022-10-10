#include <stdio.h>
#include <stdarg.h>
#include <math.h>


double fpower(double n, int pow){
    if (pow == 0)
        return 1;
    else if (pow < 0)
        return fpower(n, pow + 1) * (1. / n);
    else
        return fpower(n, pow - 1) * n;
}


double avg_geom(int n, ...){
    double res = 1;
    va_list l;
    va_start(l, n);
    for (int i = 0; i < n; i++) {
        res *= va_arg(l, double);
    }
    va_end(l);
    if (res < 0){
        return NAN;
    }
    return fpower(res, -n);
}

int main(int argc, char* argv[]){
    int com;
    printf("Please enter the command\n1) Find the a geometric mean\n2) Find a number in an integer power\n");
    scanf("%d", &com);
    if (com == 1){
        return 1; // Как вызвать функцию???
    }
    else if(com == 2){
        int pw;
        double n;
        printf("Please enter a number and a power\n");
        scanf("%lf", &n);
        scanf("%d", &pw);
        printf("The result is: %lf", fpower(n, pw));

    }
    return 0;
}