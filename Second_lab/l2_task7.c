#include <stdio.h>
#include <math.h>
#include <stdarg.h>


typedef struct coord{
    int x;
    int y;
} coord;


double polinom(double x, int n, ...);
int ifconvex(int count, ...);


int main(){
    printf("Counted Polinominal is %lf\n", polinom(2.0, 2, 1., 3., 4.));
    if (ifconvex(8, 0, 0, 0, 1, 1, 1, 1, 0))
        printf("The inserted polygon is convex!\n");
    else
        printf("The inserted polygon is not convex\n");
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


int ifconvex(int count, ...){
    int step = count / 2;
    coord coordinated[step];
    if (!(count&1) && count > 5){
        va_list l;
        va_start(l, count);
        for (int i = 0; i < step; i++) {
            coordinated[i].x = va_arg(l, int);
            coordinated[i].y = va_arg(l, int);
        }
        va_end(l);
        int sign;
        for (int i = 0; i < step; i++) {
            int ixy1 = (i + 1) % step, ixy = i % step, ixy2 = (i + 2) % step;
            int x1 = coordinated[ixy1].x - coordinated[ixy].x;
            int y1 = coordinated[ixy1].y - coordinated[ixy].y;
            int x2 = coordinated[ixy2].x - coordinated[ixy].x;
            int y2 = coordinated[ixy2].y - coordinated[ixy].y;
            int det = x1 * y2 - x2 * y1;
            if (!i)
                sign = (det > 0);
            else if (sign != (det > 0))
                return 0;
        }
        return 1;
    }
    return -1;
}
