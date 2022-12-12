#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  FILE_ERROR = -3,
  DONE = 2,
  HANDLE = 3
};

enum MODES{
    IN_FILE = 0,
    STDIN_INP = 1,
    ARGV_INP = 2
};

int handler(int code);
int take_chars(FILE* fin, FILE* fout, char* argv[], int size, const int mode);
int read_files(FILE*** file, FILE* fout, int len);
int get_str(char** buf, FILE* fin, int *flag);


int main(int argc, char *argv[]) {
    FILE* fin = NULL;
    FILE* fout = NULL;
    char* words[] = {"\nSORRY, could not open a file!\n", "\nSORRY not enough arguments\n", "\nIts Done!\n", "\n"};
    fout = fopen("to_file.txt", "w");
    int flag;
    if (!fout || argc < 2){
        printf("%s", words[argc < 2]);
        return HANDLE;
    }
    if (argc == 3 && !strcmp(argv[1], "-fi")) {
        if((fin = fopen(argv[2], "r")) != NULL){
            flag = handler(take_chars(fin, fout, NULL, 0, IN_FILE));
            fclose(fin);
            printf("%s", words[flag]);
            
        }
        else{
            printf("%s", words[0]);
            return FILE_ERROR;
        }
    }
    else if (!strcmp(argv[1], "-cin")){
        flag = handler(take_chars(NULL, fout, NULL, 0, STDIN_INP));
        printf("%s", words[flag]);
    }
    else if (!strcmp(argv[1], "-arg")){
        flag = handler(take_chars(NULL, fout, argv, argc, ARGV_INP));
        printf("%s", words[flag]);
    }
    fclose(fout);
    return flag;
}


int take_chars(FILE* fin, FILE* fout, char* argv[], int size, const int mode){
    int fsize = 2, flag = 1, capture = 0, actual = 0, curr = 0, c;
    char* buff = NULL;
    char* mess[] = {"\nGetting chars from files in a file!\n", "\nPlease enter filenames! If you want to stop, enter \"stop\"!\n", "\nGetting chars from argv!\n"};
    FILE** files = NULL;
    FILE** tmp = NULL;
    FILE* file = NULL;
    printf("%s", mess[mode]);
    if (mode == ARGV_INP){
        actual = size - 2;
        files = (FILE**)malloc(actual*sizeof(FILE*));
        if (!files){
            return NO_MEMORY;
        }
        for(int i = 2; i < size; i++){
            if ((file = fopen(argv[i], "r")) == NULL)
                return FILE_ERROR;
            files[i-2] = file;
        }
    }
    else{
        files = (FILE**)malloc(fsize*sizeof(FILE*));
        if (!files){
            return NO_MEMORY;
        }
        while (flag){
            get_str(&buff, fin, &flag);
            if (mode == STDIN_INP && !strcmp(buff, "stop")){
                break;
            }
            if((file = fopen(buff, "r")) == NULL){
                free(files);
                return FILE_ERROR;
            }
            if (actual == fsize){
                fsize<<=1;
                tmp = (FILE**)realloc(files, (fsize)*sizeof(FILE*));
                if (!tmp){
                    free(files);
                    return NO_MEMORY;
                }
                files = tmp;
            }
            free(buff);
            buff = NULL;
            files[actual++] = file;
        }
        tmp = (FILE**)realloc(files, actual*sizeof(FILE*));
        if (!tmp){
            free(files);
            return NO_MEMORY;
        }
        files = tmp;
    }
    read_files(&files, fout, actual);
    free(files);
    return DONE;
}


int get_str(char** buf, FILE* fin, int *flag){
  char c = (fin == NULL ? getchar() : fgetc(fin));
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
    c = (fin == NULL ? getchar() : fgetc(fin));
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
  *flag = (c != EOF);
  return DONE;
}



int read_files(FILE*** files, FILE* fout, int len){
    int capture, actual = len, curr = 0;
    char c;
    while (capture != actual)
    {
        if(curr == actual){
            curr = 0;
            capture = 0;
        }
        if ((*files)[curr] == NULL){
            capture++;
        }
        else if ((c = fgetc((*files)[curr])) != EOF){
            fputc(c, fout);
        }
        else{
            fclose((*files)[curr]);
            (*files)[curr] = NULL;
        }
        curr++;
    }
    return DONE;
}


int handler(int code){
    switch (code)
    {
    case FILE_ERROR:
        printf("\nSORRY could not open a file\n");
        return HANDLE;
    case NO_MEMORY:
        printf("\nSORRY no memory\n");
        return HANDLE;
    case INPUT_ERROR:
        printf("\nSORRY wrong input\n");
        return HANDLE;
    default:
        return DONE;
    }
}