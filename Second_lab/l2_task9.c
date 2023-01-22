#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define CH_NUM(ch) (isdigit(ch) ? ch - '0' : toupper(ch) - 'A' + 10)
#define NUM_CH(num) (num < 10 ? num + '0' : num - 10 + 'A')

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

int add_zero(char** str);
int if_zeros(char* str);
int del_zeros(char** str);
int sum_two(char **result, char **num, int base);
int sum_all(char** buff, int base, int n, ...);

int main(){
    char* bf = NULL;
    if(sum_all(&bf, 10, 2, "10", "11") == DONE){
        del_zeros(&bf);
        printf("Result %s\n", bf);
        free(bf);
    }
    return DONE;
}


int sum_two(char** result, char** num, int base){
    int code = del_zeros(num);
    if (code == NO_MEMORY)
        return code;
    int number_index = strlen(*num) - 1;
    int result_index = strlen(*result) - 1;
    int remember = 0;
    char addNum;
    while (result_index > 0 || number_index >= 0)
    {
        addNum = number_index < 0 ? '0' : (*num)[number_index];
        int sum = CH_NUM(addNum) + CH_NUM((*result)[result_index]) + remember;
        (*result)[result_index] = NUM_CH(sum % base);
        remember = sum / base;
        result_index--;
        if (result_index < 0)
        {
            add_zero(result);
            result_index++;
        }
        number_index--;
    }
    if (remember)
    {
        (*result)[result_index] = NUM_CH(remember);
    }
    return DONE;
}


int sum_all(char** buff, int base, int n, ...){
    if (n <= 0 || (base < 2 && base > 32)){
      return INPUT_ERROR;
    }
    int init_size = 2, size = 0;
    char* tmp;
    *buff = (char*)malloc(sizeof(char)*init_size);
    if (!*buff)
    {
      return NO_MEMORY;
    }
    (*buff)[0] = '0';
    (*buff)[1] = '\0';
    va_list l;
    va_start(l, n);
    for (int i = 0; i < n; i++) {
        tmp = va_arg(l, char*);
        if (!if_zeros(tmp))
            continue;
        char* bf2 = (char*)malloc(sizeof(char)* (strlen(tmp) + 2));
        if (!bf2){
            free(*buff);
            return NO_MEMORY;
        }
        strcpy(bf2, tmp);
        if (strlen(tmp) > init_size)
        {
            init_size = strlen(tmp)*2;
            char * tmp2 = (char*)realloc(*buff, (init_size)*sizeof(char));
            if (!tmp2){
                free(*buff);
                free(bf2);
                return NO_MEMORY;
            }
            *buff = tmp2;
        }
        if(sum_two(buff, &bf2, base) == NO_MEMORY){
            return NO_MEMORY;
        }
        free(bf2);
    }
    return DONE;
}


int if_zeros(char* str){
    int flag = 0, i = 0;
    while (str[i])
    {
        if (str[i] != '0')
        {
            flag = 1;
            break;
        }
        i++;
    }
    return flag;
}

int del_zeros(char **str){
    if ((*str)[0] != '0')
    {
        return DONE;
    }
    int counter = 0;
    for (int i = 0; i < strlen(*str); i++)
    {
        if ((*str)[i] != '0')
            break;
        counter++;
    }
    int numSize = strlen(*str) - counter;
    char* tmp = (char *)malloc(sizeof(char) * (numSize + 1));
    if (!tmp)
    {
        return NO_MEMORY;
    }
    strcpy(tmp, (*str) + counter);
    free(*str);
    *str = tmp;
    return DONE;
}

int add_zero(char** str)
{
    char tmp1 = (*str)[0];
    char tmp2 = (*str)[1];
    for (int i = 1; (*str)[i - 1] != '\0'; i++)
    {
        (*str)[i] = tmp1;
        tmp1 = tmp2;
        tmp2 = (*str)[i + 1];
    }
    (*str)[0] = '0';
    return DONE;
}
