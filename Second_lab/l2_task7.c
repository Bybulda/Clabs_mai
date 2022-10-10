#include <stdio.h>
#include <math.h>
#include <stdarg.h>


double polinom(double x, int n, ...);
int ifconvex(int count, ...);


int main(){
    printf("%lf\n", polinom(2.0, 2, 1., 3., 4.));
    return 0;
}


double polinom(double x, int n, ...){
    double res = 0.;
    va_list l;
    va_start(l, n);
    for (int i = 0; i < n + 1; i++) {
        if (!i){
            res = va_arg(l, double) * x;
        } else if (i < n)
            res = (res + va_arg(l, double)) * x;
        else
            res += va_arg(l, double);
    }
    va_end(l);
    return res;
}