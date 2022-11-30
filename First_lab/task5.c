#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#define SEP(sep) ((sep == ' ' || sep == '\n' || sep == '\t'))

enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  FILE_ERROR = -3,
  DONE = 0,
  HANDLE = 1
};

int handler(int code);
int get_str(char** buf, int* flag);
int fget_str(FILE* fin, char** buf, int* flag);
int file_infiles(FILE *fin, FILE* fout);
int file_infiles(FILE *fin, FILE* fout);
int stdin_input(FILE* fout);
int from_argv(FILE* fout, char* argv[], int size);


int main(int argc, char *argv[]) {
    FILE* fin = NULL;
    FILE* fout = NULL;
    fout = fopen("to_file.txt", "w");
    int flag;
    if (!fout || argc < 2){
        argc < 2 ? printf("\nSORRY not enough arguments\n") : printf("\nSORRY, could not open a file!\n");
        return HANDLE;
    }
    if (argc == 3 && !strcmp(argv[1], "-fi")) {
        if((fin = fopen(argv[2], "r")) != NULL){
            flag = handler(file_infiles(fin, fout));
            fclose(fin);
            flag == DONE ? printf("\nIts Done!\n") : printf("\n");
            
        }
        else{
            printf("\nSORRY, could not open a file!\n");
            return FILE_ERROR;
        }
    }
    else if (!strcmp(argv[1], "-cin")){
        flag = handler(stdin_input(fout));
        flag == DONE ? printf("\nIts Done!\n") : printf("\n");
    }
    else if (!strcmp(argv[1], "-arg")){
        flag = handler(from_argv(fout, argv, argc));
        flag == DONE ? printf("\nIts Done!\n") : printf("\n");
    }
    fclose(fout);
    return flag;
}


int file_infiles(FILE *fin, FILE* fout){
    int fsize = 2, flag = 1, capture = 0, actual = 0, curr = 0, c;
    char* buff = NULL;
    FILE* file = NULL;
    FILE** files = (FILE**)malloc(fsize*sizeof(FILE*));
    FILE** tmp = NULL;
    if (!files){
        return NO_MEMORY;
    }
    while (flag){
        fget_str(fin, &buff, &flag);
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
    while (capture != actual)
    {
        if(curr == actual){
            curr = 0;
            capture = 0;
        }
        if (files[curr] == NULL){
            capture++;
        }
        else if ((c = fgetc(files[curr])) != EOF){
            fputc(c, fout);
        }
        else{
            fclose(files[curr]);
            files[curr] = NULL;
        }
        curr++;
    }
    free(files);
    return DONE;
}


int stdin_input(FILE* fout){
    int fsize = 2, flag = 1, capture = 0, actual = 0, curr = 0, c;
    char* buff = NULL;
    FILE* file = NULL;
    FILE** files = (FILE**)malloc(fsize*sizeof(FILE*));
    FILE** tmp = NULL;
    if (!files){
        return NO_MEMORY;
    }
    while (flag){
        get_str(&buff, &flag);
        if (!strcmp(buff, "stop"))
        {
            flag = 0;
        }
        else{
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
        
    }
    tmp = (FILE**)realloc(files, actual*sizeof(FILE*));
    if (!tmp){
        free(files);
        return NO_MEMORY;
    }
    files = tmp;
    while (capture != actual)
    {
        if(curr == actual){
            curr = 0;
            capture = 0;
        }
        if (files[curr] == NULL){
            capture++;
        }
        else if ((c = fgetc(files[curr])) != EOF){
            fputc(c, fout);
        }
        else{
            fclose(files[curr]);
            files[curr] = NULL;
        }
        curr++;
    }
    free(files);
    return DONE;
}


int from_argv(FILE* fout, char* argv[], int size){
    int actual = size - 1, capture = 0, curr = 0;
    char c;
    FILE* file = NULL;
    FILE** files = (FILE**)malloc(actual*sizeof(FILE*));
    for(int i = 1; i < size; i++){
        if ((file= fopen(argv[i], "r")) == NULL)
            return FILE_ERROR;
        files[i-1] = file;
    }
    while (capture != actual)
    {
        if(curr == actual){
            curr = 0;
            capture = 0;
        }
        if (files[curr] == NULL){
            capture++;
        }
        else if ((c = fgetc(files[curr])) != EOF){
            fputc(c, fout);
        }
        else{
            fclose(files[curr]);
            files[curr] = NULL;
        }
        curr++;
    }
    free(files);
    return DONE;
}


int get_str(char** buf, int* flag){
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
  *flag = (c != EOF); 
  return DONE;
}


int fget_str(FILE* fin, char** buf, int* flag){
    char c = fgetc(fin);
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
        c = fgetc(fin);
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