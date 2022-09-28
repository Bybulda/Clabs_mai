#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#define INITIAL_SIZE 128
#define STR_SIZE 16


void print_arr(int* arr, int size){
    for (int i = 0; i < size; i++){
        if (!(i%7)){
            printf("\n");
        }
        printf("%d ", arr[i]);
    }
}


char* str_init(int size){
    char* buf = (char*) malloc(sizeof(char)*size);
    memset(buf, 0, size);
    return buf;
}


char* str_realloc(char* from, int curr_size){
    char* res = str_init(curr_size);
    memset(res, 0, curr_size);
    strcpy(res, from);
    free(from);
    return res;
}


int toi(char *s){
    int n = 0;
    int neg = 0, i = 0;
    if (s[0] == '-'){
        neg = 1;
        i++;
    }
    for(i; s[i] != '\0'; i++){
        if (n > UINT_MAX/10){
            printf("Overflow error, try lower number\n");
            exit(0);
        }
        n = n * 10 + (s[i] - '0');
    }
    if (n == 0){
        printf("Only positive numbers!!\n");
        exit(0);
    }
    if (neg) return -n;
    return n;
}

int checker(int bad, int good){
    if (good < bad)
        return 0;
    return 1;
}
void odd_posix(int size, int arr_from[], int arr_to[]){
    int j=1;
    for(int i = 1; i < size; i +=2){
        arr_to[j++] = arr_from[i];
        printf("%d ", arr_from[i]);
    }
    arr_to[0] = j;
}


void even(int size, int arr_from[], int arr_to[]){
    int j=0;
    for(int i = 1; i < size; i++){
        if (!(abs(arr_from[i]) & 1)) {
            arr_to[++j] = arr_from[i];
            printf("%d ", arr_from[i]);
        }
    }
    arr_to[0] = j;
}


void greater_than_this(int size, int pos, int arr_from[], int arr_to[]){
    int minus = 0, j = 0, num = arr_from[pos], curr = 0;
    for(int i = 0; i < size; i++){
        if (i != pos && abs(num - arr_from[i]) > minus){
            minus = abs(num - arr_from[i]);
            curr = arr_from[i];
        }
    }
    printf("\nThe most distant number(by value) for %d is %d\n", arr_from[pos], curr);
    arr_to[j++] = curr;
}


void symm_before(int pos, int arr_from[], int arr_to[]){
    int sm = 0;
    for(int i = 0; i < pos; i++){
        sm += arr_from[i];
    }
    printf("\nThe sum for position %d is %d\n", pos + 1, sm);
    arr_to[1] = sm;
}


void symm_lower(int size, int pos, int arr_from[], int arr_to[]){
    int sm = 0;
    for(int i = 0; i < size; i++){
        if (arr_from[i] < arr_from[pos])
            sm += arr_from[i];
    }
    printf("\nThe sum for number %d (consists of lower numbers) is %d\n", arr_from[pos], sm);
    arr_to[1] = sm;
}


int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Enter the path to a file!!\n");
        exit(0);
    }
    int arr[INITIAL_SIZE];
    FILE *fin = fopen(argv[2], "r");
    if (!fin){
        printf("Could not open a file, try another one!\n");
        exit(0);
    }
    int size_curr = STR_SIZE;
    int elems = 0;
    char* buff = str_init(STR_SIZE);
    char c, _c = 0;
    int index = 0;
    while(!feof(fin)){
        c = fgetc(fin);
        if (isdigit(c) && !isdigit(_c)){
            if (_c == '-')
                buff[elems++] = _c;
            buff[elems++] = c;
        }
        else if (isdigit(_c) && !isdigit(c)){
            buff[elems] = '\0';
            arr[index++] = toi(buff);
            free(buff);
            buff = str_init(STR_SIZE);
            size_curr = STR_SIZE;
            elems = 0;
        }
        else if (isdigit(_c) && isdigit(c)){
            if (elems > size_curr - 2){
                buff[elems] = '\0';
                buff = str_realloc(buff, size_curr*=2);
            }
            buff[elems++] = c;
        }
        _c = c;
    }
    printf("Array from file:\n");
    print_arr(arr, index);
    printf("\n");
    if (!strcmp(argv[1], "-a")){
        int new_arr[INITIAL_SIZE];
        odd_posix(index+1, arr, new_arr);

    }
    else if (!strcmp(argv[1], "-b")){
        int new_arr[INITIAL_SIZE];
        even(index+1, arr, new_arr);
    }
    else if (!strcmp(argv[1], "-c")){
        int pos;
        int new_arr[2];
        printf("Please enter the position(not index) of an element: ");
        scanf("%d", &pos);
        if (!checker(pos, index)){
            printf("The input number is greater then array size!\n");
            exit(0);
        }
        greater_than_this(index, pos - 1, arr, new_arr);
    }
    else if (!strcmp(argv[1], "-d")){
        int pos;
        int new_arr[2];
        printf("Please enter the position(not index) of an element: ");
        scanf("%d", &pos);
        if (!checker(pos, index)){
            printf("The input number is greater then array size!\n");
            exit(0);
        }
        symm_before(pos - 1, arr, new_arr);
    }
    else if (!strcmp(argv[1], "-e")){
        int pos;
        int new_arr[2];
        printf("Please enter the position(not index) of an element: ");
        scanf("%d", &pos);
        if (!checker(pos - 1, index)){
            printf("The input number is greater then array size!\n");
            exit(0);
        }
        symm_lower(index, pos-1, arr, new_arr);
    }
    return 0;
}