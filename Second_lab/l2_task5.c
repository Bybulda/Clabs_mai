#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void arr_print(int size, int *arr){
    printf("\n");
    for(int i = 0; i < size; i++){
        if (!(i % 5)){
            printf("\n");
        }
        printf("%d ", arr[i]);
    }
}


int fill_array(int* arr, int size, int a, int b){
    int c = b - a + 1;
    for (int i = 0; i < size; i++){
        arr[i] = rand() % (c) + a;
    }
    return 0;
}

int swap(int* mx, int* mn){
    int buff = *mx;
    *mx = *mn;
    *mn = buff;
    return 0;
}


int find_min_max(int size, int *arr){
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
    swap(&arr[imx], &arr[imn]);
    return 0;
}


int fill_unique(int* arr1, int*arr2, int size, int* size_sec){
    int* buff = size_sec;
    int count = 0;
    for (int i=0; i< size; i++) {
        int f = 1;
        for (int j = 0; j < count; j++) {
            if (arr1[i] == arr2[j]) {
                f = 0;
                break;
            }
        }
        if (f)
            arr2[count++] = arr1[i];
    }
    *buff = count;
    return 0;
}


int main(){
    srand(time(NULL));
    int n, a, b, flag;
    printf("Please, enter the size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("\nPlease enter the range [a, b]\nEnter a = ");
    scanf("%d", &a);
    printf("\nEnter b = ");
    scanf("%d", &b);
    fill_array(arr, n, a, b);
    printf("\nPlease, enter the number of command\n1) Swap min and max elements\n2) Make an array of unique elements\nFlag = ");
    scanf("%d", &flag);
    if (flag == 1){
        arr_print(n, arr);
        find_min_max(n, arr);
        arr_print(n, arr);
    }
    else if (flag == 2){
        int arr1[n], counter = 0;
        fill_unique(arr, arr1, n, &counter);
        arr_print(n, arr);
        arr_print(counter, arr1);
    }
    return 0;
}