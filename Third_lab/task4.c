#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  DONE = 0,
  DOLBOEB = -7
};


typedef struct message{
  size_t id;
  char* str;
  size_t len;
}message;


int gen_symb(char** filename, int len);
int prinr_messages(message*** mess, int len);
int add_to_file(FILE* filename, message* mess);
int free_messages(char*** mess, int len);


int main(int argc, char* argv[]){
  srand(time(NULL));
  char c, del;
  int code, tries = 0;
  char suffix[] = ".CSV";
  if (argc <2 || argc > 2){
    printf("You need to start programm with one stop word!\n");
    return INPUT_ERROR;
  }
  printf("Would you like to write some messages?!\ny/n?\n");
  scanf("%с", &c);
  // printf("%d\n", code);
  while(1){
    printf("%c\n", c);
    if (tries == 3){
      printf("\nYou are adopted mf!\n");
      return DOLBOEB;
    }
    else if (c == 'y' || c == 'n')
      break;
    else{
      printf("\nYou have %d more tries and then the app will be shut down\ny/n?\n", 3 - tries++);
      scanf("%c", &c);
    }
  }
  return 0;
}


int gen_symb(char** filename, int len){
  *filename = (char*)calloc(len, sizeof(char));
  if (!*filename)
    return NO_MEMORY;
  int ver = 0, init = len - 1;
  for(int i = 0; i < len; i++){
    ver = rand() & 1;
    switch (ver) {
      case 0:
        (*filename)[i] = rand()&31 + 65;
        break;
      case 1:
        (*filename)[i] = rand()&9 + 48;
        break;
    }
  }
  (*filename)[init] = '\0';
  return DONE;
}

int prinr_messages(message*** mess, int len){
  printf("Messages from struct:\n");
  printf("| id | message |\n");
  for(int i = 0; i < len; i++){
    printf("|%d|%s|\n", (*mess)[i]->id, (*mess)[i]->str);
  }
  return DONE;
}
