#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"



int separator(int sep){
    if (sep == ' ' || sep == '\n' || sep == '\t'){
        return 1;
    }
    return 0;
}


int check_mem(char* buff){
    if (buff == NULL)
        return 0;
    return 1;
}

char* str_init(int size){
    char* buf = (char*) malloc(sizeof(char)*size);
    memset(buf, 0, size);
    return buf;
}


char* str_realloc(char* from, int curr_size){
    char* res = str_init(curr_size);
//    memset(res, 0, curr_size);
    strcpy(res, from);
    free(from);
    return res;
}


void file_write(FILE* fin, FILE* fout){
    int c;
    while((c = fgetc(fin)) != EOF){
        fputc(c, fout);
    }
}


void file_infiles(FILE *fin, FILE* fout){
    int c, _c=0, num = 0;
    int sized = 0, curr_size = 16;
    char *buff = NULL;
    FILE *fin2 = NULL;
    while ((c = fgetc(fin) != EOF)){
        if (!separator(c) && separator(_c)){
            sized = 0;
            curr_size = 16;
            buff = str_init(curr_size);
        }
        if (!separator(c)){
            if (sized > curr_size - 2){
                buff[sized] = '\0';
                buff = str_realloc(buff, curr_size*=2);
            }
            buff[++sized] = c;
        }
        else if(separator(c) && !separator(_c)){
            fin2 = fopen(buff, "r");
            file_write(fin2, fout);
            fclose(fin2);
            free(buff);
        }
        _c = c;
    }
}


void stdin_input(FILE* fout){
    int c, _c=0, num = 0;
    int sized = 0, curr_size = 16;
    char *buff = NULL;
    FILE *fin2 = NULL;
    while ((c = getchar() != EOF)){
        if (!separator(c) && separator(_c)){
            sized = 0;
            curr_size = 16;
            buff = str_init(curr_size);
        }
        if (!separator(c)){
            if (sized > curr_size - 2){
                buff[sized] = '\0';
                buff = str_realloc(buff, curr_size*=2);
            }
            buff[++sized] = c;
        }
        else if(separator(c) && !separator(_c)){
            fin2 = fopen(buff, "r");
            file_write(fin2, fout);
            fclose(fin2);
            free(buff);
        }
        _c = c;
    }
}


int from_argv(FILE* fout, char* argv[], int size){
    FILE* fin = NULL;
    for(int i = 1; i < size; i++){
        if ((fin = fopen(argv[i], "r")) == NULL)
            return 0;
        file_write(fin, fout);
    }
    return 1;
}



int main(int argc, char *argv[]) {
    FILE* fin = NULL;
    FILE* fout = NULL;
//    if ((fin == NULL) || (fout == NULL)){
//        printf("Wrong files, try another!\n");
//        exit(0);
//    }
    fout = fopen("to_file.txt", "w");
    if (!strcmp(argv[1], "-fi")) {
        fin = fopen(argv[2], "r");
        file_infiles(fin, fout);
    }
    else if (!strcmp(argv[1], "-cin")){
        stdin_input(fout);
    }
    else if (!strcmp(argv[1], "-arg")){
        from_argv(fout, argv, argc);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}