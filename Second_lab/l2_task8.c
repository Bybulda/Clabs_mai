#include <stdio.h>
#include <math.h>

double f(double x){
    return 0.6 * pow(3, x) - 2.3 * x - 3;
}

double dihot(double (*f)(double), double start, double end, int acc){
    double point = 0.;
    double eps_acc = pow(10., -acc);
    while(fabs(start - end) >= eps_acc){
        point = (start + end) / 2.;
        if (f(start) * f(end) < eps_acc)
            start = point;
        else
            end = point;
    }
    return point;
}

int main(){
    printf("%lf", dihot(f, 2., 3., 3));
    return 0;
}