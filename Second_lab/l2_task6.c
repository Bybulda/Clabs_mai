#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define DEL(c) (c != EOF && c != '\n')
#define FOUND(text_pos, pattern, pos) printf("<String %d> <Pattern \'%s\'> <First interaction on  pos \'%d\'>\n", text_pos, pattern, pos)
#define NOT_IN_text(text, pattern, pos) printf("There is no \'%s\' in \'%s\' in string %d\n", pattern, text, pos)


enum ERRORS {
  NO_MEMORY = -1,
  INPUT_ERROR = -2,
  FILE_ERROR = -3,
  DONE = 0,
  HANDLE = 1,
  NOT_FOUND = 2
};

int get_text(char** buf, FILE* fin, int *flag);
int text_search(char* text, char* pattern, int n, int m, int *first_pos);
int file_check(FILE* file, char* pattern, int patt_len);
int file_text_search(char*text, int count,...);

int main(){
  int code = file_text_search("  ", 3, "f1", "f2", "f3");
  return 0;
}

int text_search(char* text, char* pattern, int n, int m, int *first_pos){
  if (*pattern == '\0' || n == 0){
      return NOT_FOUND;
      }
  if (*text == '\0' || n > m){
      return NOT_FOUND;
      }
  int *next = (int*)malloc((n)*sizeof(int));
  if (!next){
    return NO_MEMORY;
  }
  next[0] = 0;
  int l = 1, j = 0;
  for (l; pattern[l]; ++l)
  {
    j = next[l - 1];
    while ((j > 0) && (pattern[l] != pattern[j])) 
      j = next[j - 1];                      
    if (pattern[l] == pattern[j])                 
      ++j;
    next[l] = j;
  }
  j = 0; 
  for (int i = 0; text[i]; ++i)
  {
    while ((j > 0) && (text[i] != pattern[j]))
      j = next[j - 1];
    if (text[i] == pattern[j])
      ++j;               
    if (j == l){
      *first_pos = i - l + 1;
      free(next);
      return DONE;
      }         
  }
  free(next);
  return NOT_FOUND;
}
  

int file_check(FILE* file, char* pattern, int patt_len){
    int texting_pos = 1;
    char* buff = NULL;
    int flag = 1, code_search = 0, pos = 0;
    while(flag){
        if(get_text(&buff, file, &flag) == NO_MEMORY){
            fclose(file);
            return NO_MEMORY;
        }
        // printf("%s and %s\n", buff, pattern);
        int code = text_search(buff, pattern, patt_len, strlen(buff), &pos);
        if (code == DONE){
            FOUND(texting_pos, pattern, pos);
        }
        else if (code == NO_MEMORY){
            free(buff);
            return code;
        }
        else{
            NOT_IN_text(buff, pattern, texting_pos);
        }
        free(buff);
        texting_pos++;
    }
    return DONE;
}


int file_text_search(char* text, int count,...){
    FILE* file = NULL;
    char* filename = NULL;
    int pattern_len = strlen(text), code;
    va_list l;
    va_start(l, count);
    for (int i = 0; i < count; i++) {
        filename = va_arg(l, char*);
        if (!(file = fopen(filename, "r"))){
            return FILE_ERROR;
        }
        printf("Working with file \'%s\'\n\n", filename);
        code = file_check(file, text, pattern_len);
        fclose(file);
        file = NULL;
        if (code == NO_MEMORY)
        {
          return NO_MEMORY;
        }
    }
    va_end(l);
    return DONE;
}


int get_text(char** buf, FILE* fin, int *flag){
  char c = (fin == NULL ? getchar() : fgetc(fin));
  char* tmp = NULL;
  int initial_size = 2, len = 0;
  *buf = (char*)malloc(initial_size*sizeof(char));
  if (!*buf){
    return NO_MEMORY;
  }
  while(DEL(c)){
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
