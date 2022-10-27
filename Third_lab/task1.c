#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

int reverse(char* str){
    int ln = strlen(str);
    char* copy = str;
    char * pre = str + ln - 1;
    while (copy < pre){
        char buff = *copy;
        *copy = *pre;
        *pre = buff;
        *copy++;
        *pre--;
    }
    return DONE;
}

int traverse_num(char** str, int num, int r){
  char symb[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  int bases[] = {0, 1, 3, 7, 15, 31};
  int initial_size = 2, real = 0, ost;
  *str = (char*)malloc(sizeof(char)*initial_size);
  if (!str){
    return NO_MEMORY;
  }
  while(num != 0){
    ost = num&bases[r];
    if (initial_size == real){
      initial_size <<= 1;
      *str = (char*) realloc(*str, initial_size);
      if (*str == NULL){
        return NO_MEMORY;
      }
    }
    (*str)[real] = symb[ost];
    num = num>>r;
    real++;
  }
  if (num < 0){
    if (initial_size == real){
      initial_size <<= 1;
      *str = (char*) realloc(*str, initial_size);
      if (*str == NULL){
        return NO_MEMORY;
      }
    }
    (*str)[real++] = '-';
  }
  (*str)[real] = '\0';
  return DONE;
}

int main(){
  int scale, num, code = 0;
  printf("Please enter the scale of the base to traverse number like 2^r, r = ");
  code = scanf("%d", &scale);
  if (code != 1){
    printf("\nYou entered not an integer value\n");
    return INPUT_ERROR;
  }
  printf("\nPlease enter a number to traverse, num = ");
  code = scanf("%d", &num);
  if (code != 1){
    printf("\nPLease enter an integer number\n");
    return INPUT_ERROR;
  }
  if (scale < 1 || scale > 5){
    printf("\nThe r value must be in range [1, 5]\n");
    return INPUT_ERROR;
  }
  char* str = NULL;
  code = traverse_num(&str, num, scale);
  if (code == DONE){
    reverse(str);
    printf("\nSo number %d was traversed to %s in base 2^%d = %d\n", num, str, scale, 1<<scale);
    free(str);
  }
  else if (code == NO_MEMORY){
    printf("\nNo memory, try again later!\n");
    return NO_MEMORY;
  }
  return DONE;
}
