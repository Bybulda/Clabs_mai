#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


int if_overflow(int a, int b){
    if (a > INT_MAX - b){
        return 1;
    }
    return 0;
}

int print_array(int* arr, int size){
    for (int i = 0; i < size; i++){
        !(i % 8) ? printf("\n%d ", arr[i]) : printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int fill_array(int* arr, int size){
    for (int i = 0; i < size; i++){
        arr[i] = rand();
    }
    return 0;
}


int new_arr(int* arr1, int* arr2, int* arr, int size, int minsiz){
    for(int i = 0; i<size;i++){
        if (i > minsiz - 1){
            if (if_overflow(arr1[i], arr2[minsiz - 1]))
                return 1;
            arr[i] = arr1[i] + arr2[minsiz - 1];
        }
        else{
            if (if_overflow(arr1[i], arr2[i]))
                return 1;
            arr[i] = arr1[i] + arr2[i];
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));
    int n, m;
    printf("Please, enter the size of the first array: ");
    scanf("%d", &n);
    printf("\nPlease, enter the size of the second array: ");
    scanf("%d", &m);
    int arr[n], arr2[m], arr3[n];
    fill_array(arr, n);
    fill_array(arr2, m);
    int flag = new_arr(arr, arr2, arr3, n, m);
    if (!flag){
        print_array(arr, n);
        print_array(arr2, m);
        print_array(arr3, n);
    }
    else
        printf("Something went wrong, pls try again later\n");
    return 0;
}