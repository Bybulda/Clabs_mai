#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

int lg(int num, int base);
int reverse(char* str);
int traverse_num(char** str, int num, int r);


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
    printf("\nSo number %d was traversed to %s in base 2^%d = %d\n", num, str, scale, 1<<scale);
    free(str);
  }
  else if (code == NO_MEMORY){
    printf("\nNo memory, try again later!\n");
    return NO_MEMORY;
  }
  return DONE;
}


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

int lg(int num, int base){
  int start = 1, scale = 0;
  while(start < num){
    scale++;
    start<<=base;
  }
  return scale;
}


int traverse_num(char** str, int num, int r){
  char symb[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  int bases[] = {0, 1, 3, 7, 15, 31};
  int flag = 0, ost;
  if (num < 0){
    flag++;
    num = -num;
  }
  int initial_size = lg(num, r) + 1 + flag;
  *str = (char*)calloc(initial_size, sizeof(char));
  if (!str){
    return NO_MEMORY;
  }
  int real = initial_size - 2;
  if(flag)
    (*str)[0] = '-';
  while(num != 0){
    ost = num&bases[r];
    (*str)[real--] = symb[ost];
    num = num>>r;
  }
  (*str)[initial_size - 1] = '\0';
  return DONE;
}
