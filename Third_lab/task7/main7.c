#include "task7.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char* argv[]){
  if (argc != 2){
    printf("Please start the programm with a filename\n");
    return INPUT_ERROR;
  }
  FILE* file = fopen(argv[1], "r");
  if (!file){
    printf("File could not open\n");
    return FILE_ERROR;
  }
  int code;
  civ_node* head = NULL;
  code = list_init(&head);
  if (code == NO_MEMORY){
    printf("No memory!!\n");
    return NO_MEMORY;
  }
}
