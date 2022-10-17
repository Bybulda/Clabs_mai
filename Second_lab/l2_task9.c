#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

enum EXIT_CODE{
  INPUT_ERROR = -1;
  NO_MEMORY = -2;
  DONE_STATUS = 0;
};

char* squeeze(char* str1);
char* sum_two(char* str1, char* str2, int base);
int sum_all(char* buff,int base, int n, ...);

int main(){
    return 0;
}


char* squeeze(char* str1);

char* sum_two(char* str1, char* str2, int base){
    if (str1[0] == '0')
      str1 = squeeze(str1);
    if (str2[0] == '0')
      str2 = squeeze(str2);
    int ln1 = strlen(str1);
    int ln2 = strlen(str2);
}


int sum_all(char* buff,int base, int n, ...){
    if (n <= 0){
      return INPUT_ERROR;
    }
    char* bf1 = NULL;

    va_list l;
    va_start(l, n);
    for (size_t i = 0; i < n; i++) {
        if (bf1 == NULL)
          bf1 = va_arg(l, char*);
        else
          bf1 = sum_two(bf1, va_arg(l, char*), base);
    }
    buff = *bf1;
    free(bf1);
    return DONE_STATUS;
}
