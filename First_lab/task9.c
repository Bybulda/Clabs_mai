#include <stdio.h>
#include "math.h"
#include "string.h"
#include "limits.h"
#include "stdlib.h"


enum ERRORS{
  NO_MEMORY = -1,
  WRONG_INPUT = -2,
  OVERFLOW = -3
};

char* reallocate(char* str, int size){
  char* tmp = (char*)realloc(str, size*sizeof(char));
  free(str);
  if (!tmp){
    return NULL;
  }
  return tmp;

}

int toi(char *s, int base){
    int n = 0, neg = 1;
    for(int i = 0; s[i] != '\0'; i++){
        if (n > UINT_MAX/10){
            printf("Overflow error, try lower number\n");
            exit(0);
        }
        if (s[i] == '-'){
            neg = -1;
        }

        n = n * 10 + (s[i] - '0');
    }
    return neg * n;
}


int main(int argc, char *argv[]) {
    int base, flag = 1, len = 0, bf_size = 2;
    char* buff = NULL;
    if (scanf("%d", &base) != 1){
      printf("Wrong input!\n");
      return WRONG_INPUT;
    }
    printf("\nPlease, enter numbers, if you want to stop - enter \"Stop\"\n");
    while(flag){

    }
    return 0;
}
