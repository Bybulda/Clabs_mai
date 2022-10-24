#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int num_bits(int k);
int check_bits(int l, int num, int straight);
void bits_in(int l, int k, int** arr, int* len, int* code, int flag);
void print_arr(int* arr, int ln);

enum ERRORS{
  INPUT_ERROR = -1,
  OVERFLOW = -2,
  NO_MEMORY = -3,
  DONE_IN = 1,
  DONE_STRAIGHT = 2,
  NOT_FOUND = -4,
  DONE = 0
};

int main(){
  int l, k, check = 0;
  int* in = NULL;
  int* straight = NULL;
  int ln1 = 0;
  int ln2 = 0;
  printf("Please, enter l; ");
  check = scanf("%d", &l);
  if (!check){
    printf("\nPlease, enter correct number\n");
    return INPUT_ERROR;
  }
  printf("\nPlease, enter k; ");
  check = scanf("%d", &k);
  if (!check){
    printf("\nPlease, enter correct number\n");
    return INPUT_ERROR;
  }
  if (l > k){
    printf("\nL cannot exceed k!\n");
    return INPUT_ERROR;
  }
  bits_in(l, k, &in, &ln1, &check, 0);
  if (check == DONE_IN){
    print_arr(in, ln1);
    free(in);
  }
  else if(check == NO_MEMORY){
    printf("Memory error!\n");
    return NO_MEMORY;
  }
  else if(check == NOT_FOUND)
    printf("Numbers for l=%d and k=%d werent found\n", l, k);
  check = 0;
  bits_in(l, k, &straight, &ln2, &check, 1);
  if (check == DONE_STRAIGHT){
    print_arr(straight, ln2);
    free(straight);
  }
  else if(check == NO_MEMORY){
    printf("Memory error!\n");
    return NO_MEMORY;
  }
  else if(check == NOT_FOUND)
    printf("Numbers for l=%d and k=%d werent found\n", l, k);
  return DONE;
}


int num_bits(int k){
  return 2<<(k - 1);
}

int check_bits(int l, int num, int straight){
  int counter = 0;
  if (!straight){
    while(num != 0){
      counter += (num&1);
      num>>=1;
    }
  }
  else{
    while(num != 0){
      if (!(num&1)){
        if (counter == l)
          break;
        counter = 0;
      }
      else
        counter++;
      num>>=1;
    }
  }
  return counter == l;
}


void bits_in(int l, int k, int** arr, int* len, int* code, int flag){
  int pred = num_bits(k - 1);
  int lim = num_bits(k);
  int size = 0;
  for (int i = pred; i < lim; i++){
    if(check_bits(l, i, flag)){
      if(size == *len){
        size = size ? size*2 : 1;
        *arr = (int*)realloc(*arr, size*sizeof(int));
        if(!*arr){
          *code = NO_MEMORY;
          return;
        }
      }
      (*arr)[(*len)++] = i;
    }
  }
  *code = size ? (flag ? DONE_STRAIGHT : DONE_IN) : NOT_FOUND;
  return;
}

void print_arr(int* arr, int ln){
  for(int i = 0; i < ln; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}
