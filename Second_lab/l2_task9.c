#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

enum EXIT_CODE{
  INPUT_ERROR = -1,
  NO_MEMORY = -2,
  DONE_STATUS = 0
};

char* squeeze(char* str1, int ln);
char* sum_two(char* str1, char* str2, int base);
int sum_all(char* buff, int base, int n, ...);

int main(){
    int base = 2, check = 1;
    printf("Please enter the base of numbers in range [2, 32]!\n");
    if (!scanf("%d", &base))
      printf("Incorrect base!\n");
      return INPUT_ERROR;
    char* bf = NULL;
    check = sum_all(bf, base, 2, "0001011", "1011");
    return DONE_STATUS;
}


char* squeeze(char* str1, int ln){
    char* tmp = str1;
    int zeros = 0;
    while(*tmp == '0'){
      zeros++;
      *tmp++;
    }
    char* st = NULL;
    st = (char*)malloc(sizeof(char) * (ln - zeros));
    char* pptr = st;
    while(*tmp)
      *pptr++ = *tmp++;
    printf("%s\n", st);
    free(str1);
    return st;

}

char* sum_two(char* str1, char* str2, int base){
    int ln1 = strlen(str1);
    int ln2 = strlen(str2);
    char* st1 = NULL;
    char* st2 = squeeze(str2, ln2);
    st1 = squeeze(str1, ln1);
    printf("%s\n", st1);

}


int sum_all(char* buff, int base, int n, ...){
    if (n <= 0 || (base < 2 && base > 32)){
      return -1;
    }
    char* bf1 = NULL;

    va_list l;
    va_start(l, n);
    for (size_t i = 0; i < n; i++) {
        if (!i)
          bf1 = va_arg(l, char*);
        else
          bf1 = sum_two(bf1, va_arg(l, char*), base);
    }
    buff = bf1;
    free(bf1);
    return 0;
}
