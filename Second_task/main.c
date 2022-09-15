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


double find_x(int b, int a, double d){
    return ((-b)+d) / (2*a);
}


float descrim(int a, int b, int c){
    return pow(b * b - 4 * a * c, 0.5);
}


int f_x(int a, int b, int c){
    float mass[3] = {a, b, c};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            return 0;
        }
    }
}


int kratn(int a, int b){
    return !(a%b);
}


int if_triangle(int a, int b, int c){
    if ((a + b > c && c > a && c > b) || (a + c > b && b > c && b > a)
    || (c + b > a && a > c && a > b)){
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    int n;
    if (argc<3){
        printf("U must enter a number and a flag!\nExample: <number> </q or -q>\n");
    }
    else if (argc == 3 && (!strcmp(argv[1], "-q") || !strcmp(argv[1], "/q"))){
        n = toi(argv[1]);
//        kratn(n);
    }
    else if (argc == 2 && (!strcmp(argv[1], "-m") || !strcmp(argv[1], "/m"))){
        kratn(toi(argv[2]), toi(argv[3]));
    }
    else if (argc == 3 && (!strcmp(argv[2], "-t") || !strcmp(argv[2], "/t"))){
        if_triangle(toi(argv[2]), toi(argv[3]), toi(argv[4]));
    }
    else{
        printf("Something went wrong, try again pls\n");
    }
    return 0;
}