#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>


enum ERRORS{
  NO_MEMORY = -1,
  WRONG_INPUT = -2,
  DONE = 0
};


int traverse_num(char** str, int num, int base){
  int ost = base - 1, init = 33, len = 31, del = 0, size = 0;
  char* tmp = NULL;
  free(*str);
  *str = (char*)calloc(init, sizeof(char));
  if (!*str){
    return NO_MEMORY;
  }
  tmp = (*str) + len;
  while(num){
    del = num%base;
    (*str)[len--] = del > 9 ? del - 10 + 'A' : '0' + del;
    num = num / base;
    size++;
    tmp--;
  }
  tmp++;
  strcpy((*str), tmp);
  return DONE;
}

int reversed_toi(char *s, int base, int size){
    int n = 0, index = size;
    int tmp = 1;
    while(index-- != 0){
        if (s[index] == '-'){
          break;
        }
        n += (isdigit(s[index]) ? (s[index] - '0') : (tolower(s[index]) - 'a' + 10)) * tmp;
        tmp *= base;
    }
    return n;
}


int get_str(char** buf, int* size){
  char c = getchar();
  char* tmp = NULL;
  int initial_size = 2, len = 0;
  *buf = (char*)malloc(initial_size*sizeof(char));
  if (!*buf){
    return NO_MEMORY;
  }
  while(c != EOF && c != '\n' && c != ' '){
    if (len == initial_size){
      initial_size<<=1;
      tmp = (char*)realloc(*buf, initial_size);
      if (!tmp){
        free(*buf);
        return NO_MEMORY;
      }
      *buf = tmp;
    }
    (*buf)[len++] = c;
    c = getchar();
  }
  if (len == initial_size){
    initial_size++;
    tmp = (char*)realloc(*buf, initial_size);
    if (!tmp){
      free(*buf);
      return NO_MEMORY;
    }
    *buf = tmp;
  }
  (*buf)[len] = '\0';
  *size = len;
  return DONE;
}


int main(int argc, char *argv[]) {
    int base, flag = 1, max = 0, num = 0, size = 0;
    char* buff = NULL;
    char* str_num = NULL;
    char del;
    printf("Please, enter the base of the system in range [2, 36]: ");
    if (scanf("%d%c", &base, &del) != 2){
      printf("Wrong input!\n");
      return WRONG_INPUT;
    }
    printf("\nPlease, enter numbers, if you want to stop - enter \"Stop\"\n");
    while (flag){
      get_str(&buff, &size);
      if (!strcmp(buff, "Stop")){
        flag = 0;
      }
      else{
        num = reversed_toi(buff, base, size);
        if (num == WRONG_INPUT){
          printf("Wrong base!\n");
          return WRONG_INPUT;
        }
        if (num > max){
          max = num;
        }
      size = 0;
      free(buff);
      buff = NULL;
      }
    }
  printf("Max number in system 10 = %d\n", max);
  traverse_num(&buff, max, 9);
  printf("Max number in system 9 = %s\n", buff);
  traverse_num(&buff, max, 18);
  printf("Max number in system 18 = %s\n", buff);
  traverse_num(&buff, max, 27);
  printf("Max number in system 27 = %s\n", buff);
  traverse_num(&buff, max, 36);
  printf("Max number in system 36 = %s\n", buff);
  return 0;
}
