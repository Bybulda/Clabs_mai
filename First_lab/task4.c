#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#define SIZE 16


char* str_init(int size){
    char* buf = ((char*) malloc(size * sizeof(char)));
    return buf;
}


char* str_realloc(char* from, int curr_size){
    char* res = str_init(curr_size*2);
    while(*from){
        *res++ = *from++;
    }
    free(from - curr_size + 1);
    return res;
}


int main(int argc, char *argv[]){
    FILE *fin = fopen(argv[1], "r");
    int curr_size = SIZE;
    char *buff = NULL;
//    if (fin == NULL){
//        printf("Could not open this file, try again");
//        exit(0);
//    }
    buff = str_init(curr_size);
    for (int i = 0; i < SIZE; ++i) {
        if (i == 15){
            buff[i] = '\0';
        }
        else{
            buff[i] = (char) (i+65);
        }
    }
    printf("%s\n", buff);
    buff = str_realloc(buff, curr_size);
    for (int i = curr_size+1; i < SIZE*2; ++i) {
        if (i == 31){
            buff[i] = '\0';
        }
        else{
            buff[i] = (char) (i+65);
        }
    }
    printf("%s\n", buff);
}