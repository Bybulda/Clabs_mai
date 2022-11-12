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
    return 0;
}

int traverse_num(char** str, int num, int base){
  int ost = base - 1, init = 2, len = 0, del = 0;
  char* tmp = NULL;
  free(*str);
  *str = (char*)malloc(init*sizeof(char));
  if (!*str){
    return NO_MEMORY;
  }
  while(num){
    del = num%base;
    if (len == init){
      init<<=1;
      tmp = (char*)realloc(*str, init);
      if (!tmp){
        free(*str);
        return NO_MEMORY;
      }
      *str = tmp;
    }
    (*str)[len++] = del > 9 ? del - 10 + 'A' : '0' + del;
    num = num / base;
  }
  if (len == init){
      init++;
      tmp = (char*)realloc(*str, init);
      if (!tmp){
        free(*str);
        return NO_MEMORY;
      }
      *str = tmp;
    }
  (*str)[len] = '\0';
  reverse(*str);
  return DONE;
}

int reversed_toi(char *s, int base, int size){
    if (base < 2 || base > 32){
      return WRONG_INPUT;
    }
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
    printf("Please, enter the base of the system in range [2, 36]: ");
    if (scanf("%d", &base) != 1){
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
