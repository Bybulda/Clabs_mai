#include "task7.c"
// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>
// #include <stdlib.h>
// #include <math.h>


int main(){
  // if (argc != 2){
  //   printf("Please start the programm with a filename\n");
  //   return INPUT_ERROR;
  // }
  // FILE* file = fopen(argv[1], "r");
  // if (!file){
  //   printf("File could not open\n");
  //   return FILE_ERROR;
  // }
  // int code;
  // civ_node* head = NULL;
  // code = list_init(&head);
  // if (code == NO_MEMORY){
  //   printf("No memory!!\n");
  //   return NO_MEMORY;
  // }
  // printf("12.10.2003 vs 12.10.2002: %d", cmp_age("12.10.2003", "12.10.2003"));
  // printf("%d", MALE);
  civ_node* head = NULL;
  // if (list_init(&head) == NO_MEMORY)
  //   return NO_MEMORY;
  FILE* fin = fopen("f1", "r");
  FILE* fout = fopen("f3", "w");
  from_file_to_list(fin, &head);
  insert(&head, "name", "sur", "patr", "12.01.2000", 'M', 15000.12345);
  find(&head, NULL, NULL, NULL, NULL, NULL, 15000.12345);
  from_list_to_file(fout, &head);
  list_destroy(&head);
  return DONE;
}
