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
    int zero = 0;
    while(*tmp == '0'){
      zero++;
      *tmp++;
    }
    char* stt = (char*)malloc(ln - zero);
    memset(stt, 0, ln - zero);
    char* stm = stt;
    while(*tmp)
      *stm++ = *tmp++;
    *stm = '\0';
    printf("%s\n", stt);
    // free(str1);
    return stt;

}

char* sum_two(char* str1, char* str2, int base){
    int if_over = 0, flag = 0;
    int ln1 = strlen(str1);
    int ln2 = strlen(str2);
    if (ln1 > ln2){
        char* res = (char*)calloc(ln1 + 2, 1);
        int now = ln1 + 2 - 1;
        for (int i = ln2 - 1, j = ln1 - 1; i > -1; i--) {
            if (!overflow(str2[i], str1[j], base)) {
                int rs = (isdigit(str1[j]) ? str1[j] - '0' : str1[j] - 'A' + 10) + (isdigit(str2[i]) ? str2[i] - '0' : str2[i] - 'A' + 10)
                res[now--] = rs > 9 ? 'A' + rs - 10 : rs;
            }
        }
    }
    else {
        char* res = (char*)calloc(ln2 + 2, 1);
    }

    return "abcd";

}


int sum_all(char* buff, int base, int n, ...){
    if (n <= 0 || (base < 2 && base > 32)){
      return -1;
    }
    char* bf1 = NULL;
    char* tmp = NULL;

    va_list l;
    va_start(l, n);
    for (int i = 0; i < n; i++) {
        if (!i){
          bf1 = va_arg(l, char*);}
        else{
          tmp = va_arg(l, char*);
          bf1 = sum_two(bf1, tmp, base);
          }
    }
    buff = bf1;
    free(bf1);
    return 0;
}
