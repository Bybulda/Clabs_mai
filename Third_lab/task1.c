#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0
};

char* reall(char* str, int *initial_size, int* code){
  int siz = *initial_size;
  *initial_size = siz<<1;
  char* buff = (char*)calloc(*initial_size, sizeof(char));
  if (!buff){
    *code = NO_MEMORY;
    free(str);
    return " ";
  }
  buff[*initial_size] = '\0';
  for (int i = siz, j = *initial_size; i > -1; i--){
    buff[--j] = str[i];
  }
  free(str);
  *code = DONE;
  return buff;


}

char* traverse_num(int num, int r, int* code){
  char symb[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
  int bases[] = {0, 1, 3, 7, 15, 31};
  int initial_size = 2, real = 0, ost, current = initial_size;
  char* str = (char*)malloc(sizeof(char)*initial_size);
  if (!str){
    *code = NO_MEMORY;
    return " ";
  }
  while(num != 0){
    ost = num&bases[r];
    real++;
    if (initial_size == real){
      str = reall(str, &initial_size, code);
    }
    current = initial_size - real;
    str[current] = symb[ost];
    num = num<<r;
  }
}

int main(){
  int scale, num, code = 0;
  printf("Please enter the scale of the base to traverse number like 2^r, r = ");
  scanf("%d", &scale);
  printf("\nPlease enter a number to traverse, num = ");
  scanf("%d", &num);
  printf("%s\n", traverse_num(num, scale, &code));
  return 0;
}
