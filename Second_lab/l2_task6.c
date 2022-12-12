#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  FILE_ERROR = -3,
  DONE = 0,
  HANDLE = 1
};


int str_search(char* text, char* pattern, int n, int m);
int file_open(FILE* file, char* pattern);
int file_str_search(char*str, int count,...);

int main(){

    return 0;
}

int str_search(char* text, char* pattern, int n, int m){
  if (*pattern == '\0' || n == 0)
      printf("The pattern occurs with shift 0");
      return -1;
  if (*text == '\0' || n > m)
      printf("Pattern not found");
      return -1;
  int next[n + 1];
  for (int i = 0; i < n + 1; i++) {
      next[i] = 0;
  }
  for (int i = 1; i < n; i++){
      int j = next[i + 1];

      while (j > 0 && pattern[j] != pattern[i]) {
          j = next[j];
      }

      if (j > 0 || pattern[j] == pattern[i]) {
          next[i + 1] = j + 1;
      }
  }
  for (int i = 0, j = 0; i < m; i++){
      if (*(text + i) == *(pattern + j)){
          if (++j == n) {
              printf("The pattern occurs with shift %d\n", i - j + 1);
          }
      }
      else if (j > 0){
          j = next[j];
          i--;
      }
  }
  return 0;
}


int file_open(FILE* file, char* pattern){

}


int file_str_search(char*str, int count,...){
    FILE * file = NULL;
    va_list l;
    va_start(l, count);
    for (int i = 0; i < count; i++) {
        if (!(file = fopen(va_arg(l, char*), "r"))){
            return FILE_ERROR;
        }
        
    }
    va_end(l);
    return 0;
}
