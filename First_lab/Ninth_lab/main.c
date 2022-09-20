#include <stdio.h>
#include "math.h"
#include "string.h"
#include "limits.h"
#include "stdlib.h"


int toi(char *s, int base){
    int n = 0, neg = 1;
    for(int i = 0; s[i] != '\0'; i++){
        if (n > UINT_MAX/10){
            printf("Overflow error, try lower number\n");
            exit(0);
        }
        if (s[i] == '-'){
            neg = -1;
        }
        if (s[i] - '0' < 0 || s[i] - '9' > 9){
            printf("Not a number\n");
            exit(0);
        }
        n = n * 10 + (s[i] - '0');
    }
    return neg * n;
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