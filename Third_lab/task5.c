#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0,
  DOLBOEB = -7
};


typedef struct student_list{
  size_t id;
  char* name;
  char* surname;
  short course;
  short ex1;
  short ex2;
  short ex3;
  short ex4;
  short ex5;
  message* next;
}message;

int main(int argc, char* argv[]){
  char c, del;
  int code, tries = 0;
  printf("Would you like to write some messages?!\ny/n?\n");
  scanf("%с", &c);
  // printf("%d\n", code);
  while((c != 'y' && c != 'n') && tries <3){
    printf("\nYou have %d more tries and then the app will be shut down\ny/n?\n", 3 - tries++);
    scanf("%c", &c);
  }
  if (tries == 3){
    printf("\nYou are adopted mf!\n");
    return DOLBOEB;
  }
  return 0;
}
