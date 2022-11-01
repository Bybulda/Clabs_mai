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
  size_t size;
}message;

int init_message(message** mess);
int renew_mess(message** mess);
int gen_symb(char** filename, int len);
int prinr_messages(message*** mess, int len);
int add_to_file(FILE* filename, message* mess);
int free_messages(char*** mess, int len);


int main(int argc, char* argv[]){
  srand(time(NULL));
  char chr, del;
  message* mess = NULL;
  message** post = NULL;
  int code, tries = 0;
  char suffix[] = ".CSV";
  char* filename = NULL;
  if (argc <2 || argc > 2){
    printf("You need to start programm with one stop word!\n");
    return INPUT_ERROR;
  }
  code = gen_symb(&filename, 10);
  if (code == NO_MEMORY){
    printf("No memory error, try again later!\n");
    return NO_MEMORY;
  }
  strcat(filename, suffix);
  // printf("Would you like to write some messages?!\ny/n?\n");
  // while(1){
  //   code = scanf("%c%c", &del, &chr);
  //   if (tries == 3){
  //     printf("\nYou are adopted mf!\n");
  //     return DOLBOEB;
  //   }
  //   else if (chr == 'y' || chr == 'n'){
  //     break;
  //   }
  //   else{
  //     printf("\nYou have %d more tries and then the app will be shut down\ny/n?\n", 3 - tries);
  //     tries++;
  //   }
  // }
  return 0;
}


int gen_symb(char** filename, int len){
  *filename = (char*)calloc(len, sizeof(char));
  if (!*filename)
    return NO_MEMORY;
  int ver = 0, init = len - 1;
  char symb;
  for(int i = 0; i < init; i++){
    ver = rand() & 1;
    switch (ver) {
      case 0:
        symb = rand()%26 + 97;
        printf("%d\n", symb);
        (*filename)[i] = symb;
        break;
      case 1:
        symb = rand()%10 + 48;
        printf("%d\n", symb);
        (*filename)[i] = symb;
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

int init_message(message** mess){
  *mess = (message*)malloc(sizeof(message));
  if(!*mess){
    return NO_MEMORY;
  }
  (*mess)->id = 1;
  (*mess)->size = 2;
  (*mess)->len = 0;
  return DONE;
}

int renew_mess(message** mess){
  free((*mess)->str);
  (*mess)->id++;
  (*mess)->size = 2;
  (*mess)->len = 0;
}
