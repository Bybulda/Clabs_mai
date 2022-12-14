#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

int subtraction(int a, int b);
int add(int num1, int num2);
int lg(int num, int base);
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

int subtraction(int a, int b) {
    return add(a, add(~b, 1));
}

int add(int num1, int num2){
    int res = 0, carry = 0;
    res = num1^num2;
    carry = (num1&num2) << 1;
    while (carry) {
        int tmp = res;
        res = res^carry;
        carry = (tmp&carry) << 1;
    }
    return res;
}

int lg(int num, int base){
  int scale = 0;
  while(num>0){
    scale = add(scale, 1);
    num>>=base;
  }
  return scale;
}


int traverse_num(char** str, int num, int r){
  char symb[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  int bases[] = {0, 1, 3, 7, 15, 31};
  int flag = 0, ost;
  if (num < 0){
    flag = 1;
    num = -num;
  }
  int initial_size = lg(num, r);
  initial_size = flag ? add(initial_size, 2) : add(initial_size, 1);
  *str = (char*)calloc(initial_size, sizeof(char));
  if (!str){
    return NO_MEMORY;
  }
  int real = subtraction(initial_size, 2);
  if(flag)
    (*str)[0] = '-';
  while(num != 0){
    ost = num&bases[r];
    (*str)[real] = symb[ost];
    real = subtraction(real, 1);
    num = num>>r;
  }
  (*str)[subtraction(initial_size, 1)] = '\0';
  return DONE;
}
