#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>


enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

int sum_char(char a, char b);
int overflow(int base, char a, char b);
int increase(char** str, int ln);
int squeeze(char* (*str1), int ln);
int sum_two(char** str1, char* str2, int base);
int sum_all(char** buff, int base, int n, ...);

int main(){
    // int base = 2, check = 1;
    // printf("Please enter the base of numbers in range [2, 32]!\n");
    // if (!scanf("%d", &base)){
    //   printf("Incorrect base!\n");
    //   return INPUT_ERROR;
    // }
    char* bf = NULL;
    if(sum_all(&bf, 2, 2, "111", "1") == DONE){
        printf("%s", bf);
        free(bf);
    }
    return DONE;
}


int sum_two(char** str1, char* str2, int base){
    int ln1 = strlen(*str1), ln2 = strlen(str2);
    char* tmp = NULL;
    char* clear = *str1;
    if (ln1 > ln2){
        tmp = (char*)realloc(tmp, (ln1 + 2)*sizeof(char));
        if (!tmp){
            return NO_MEMORY;
        }
        tmp[0] = '0';
        int counter = ln1 + 1, remainder = 0, numeric;
        for(int i = ln1 - 1, j = ln2 - 1; j > -1;){
            numeric = sum_char((*str1)[i], str2[j]) + remainder;
            remainder = numeric / base;
            numeric = numeric % base;
            tmp[counter--] = numeric < 10 ? numeric + '0' : numeric - 10 + 'A';
            i--;
            j--;
        }
        for (int i = counter; i > -1; i--){
            numeric = (isdigit((*str1)[i]) ? (*str1)[i] - '0' : 'A' - (*str1)[i] + 10) + remainder;
            remainder = numeric / base;
            numeric = numeric % base;
            tmp[i] = numeric < 10 ? numeric + '0' : numeric - 10 + 'A';
        }
        tmp[ln1 + 1] = '\0';
    }    
    else{
        tmp = (char*)malloc((ln2 + 2)*sizeof(char));
        if (!tmp){
            return NO_MEMORY;
        }
        tmp[0] = '0';
        int counter = ln2, remainder = 0, numeric;
        for(int i = ln1 - 1, j = ln2 - 1; i > -1;){
            numeric = sum_char((*str1)[i], str2[j]) + remainder;
            remainder = numeric / base;
            numeric = numeric % base;
            tmp[i] = numeric < 10 ? numeric + '0' : numeric - 10 + 'A';
            i--;
            j--;
            counter = i;
        }
        counter++;
        for (int i = counter; i > -1; i--){
            numeric = (isdigit((*str1)[i]) ? (*str1)[i] - '0' : 'A' - (*str1)[i] + 10) + remainder;
            remainder = numeric / base;
            numeric = numeric % base;
            tmp[i] = numeric < 10 ? numeric + '0' : numeric - 10 + 'A';
        }
        tmp[ln2 + 1] = '\0';
        
    }
    free(*str1);
    *str1 = NULL;
    *str1 = tmp;
    return DONE;
}


int sum_all(char** buff, int base, int n, ...){
    if (n <= 0 || (base < 2 && base > 32)){
      return INPUT_ERROR;
    }
    char* tmp = NULL;
    va_list l;
    va_start(l, n);
    for (int i = 0; i < n; i++) {
        if (!i){
          tmp = va_arg(l, char*);
          *buff = (char*)realloc(*buff, strlen(tmp)*sizeof(char));
          if (!(*buff)){
            return NO_MEMORY;
          }
          strcpy(*buff, tmp);
          tmp = NULL;
        }
        else{
          tmp = va_arg(l, char*);
          if(sum_two(buff, tmp, base) == NO_MEMORY){
            return NO_MEMORY;
          }
        }
    }
    return DONE;
}


int sum_char(char a, char b){
    return (isdigit(a) ? a - '0' : 'A' - a + 10) + (isdigit(b) ? b - '0' : 'A' - b + 10); 
}