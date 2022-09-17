#include <stdio.h>
#include "time.h"
#include "math.h"
#include "limits.h"
#include "stdlib.h"


void find_min_max(int *arr){
    int imx = 0, imn = 0, mn = arr[0], mx = arr[0];
    for (int i = 0; i < 64; i++){
        if (arr[i] > mx){
            mx = arr[i];
            imx = i;
        }
        if (arr[i] < mn){
            mn = arr[i];
            imn = i;
        }
    }
    printf("Max number is %d, at position %d\n", mx, imx);
    printf("Min number is %d, at position %d\n", mn, imn);
    arr[imx] = mn;
    arr[imn] = mx;
}

void arr_print(int *arr){
    for(int i = 0; i < 64; i++){
        if (!(i % 8)){
            printf("\n");
        }
        printf("%d, ", arr[i]);
    }
}

int main() {
    int n[64];
    srand(time(NULL));
    for (int i = 0; i < 64; i++){
        if (!(i % 8)){
            printf("\n");
        }
        n[i] = rand();
        printf("%d, ", n[i]);
    }
    printf("\n\n");
    find_min_max(n);
    arr_print(n);
    return 0;
}