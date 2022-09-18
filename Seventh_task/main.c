#include <stdio.h>
#include "time.h"
#include "stdlib.h"


void find_min_max(int size, int *arr){
    int imx = 0, imn = 0, mn = arr[0], mx = arr[0];
    for (int i = 0; i < size; i++){
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

void arr_print(int size, int *arr){
    for(int i = 0; i < size; i++){
        if (!(i % 5)){
            printf("\n");
        }
        printf("%d ", arr[i]);
    }
}

int main() {
    printf("Please enter the size of array: n = ");
    int size;
    scanf("%d", &size);
    int n[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++){
        if (!(i % 5)){
            printf("\n");
        }
        n[i] = rand();
        printf("%d ", n[i]);
    }
    printf("\n\n");
    find_min_max(size, n);
    arr_print(size, n);
    return 0;
}