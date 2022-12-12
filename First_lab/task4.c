#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 16


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
    memset(res, 0, curr_size);
    strcpy(res, from);
    free(from);
    return res;
}


int main(int argc, char *argv[]){
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen("to_write_copy.txt", "w");
    int curr_size = SIZE;
    if (fin == NULL || fout == NULL){
        printf("Could not open files, try again\n");
        exit(0);
    }
    char* buff1 = str_init(curr_size);
    char* buff2 = str_init(curr_size);
    char* buff3 = str_init(curr_size);
    if (!check_mem(buff1) && !check_mem(buff2) && !check_mem(buff3)){
        printf("Memset error try again\n");
    }
    char c, _c=0, num = 0;
    int sized = 0;
    while (!feof(fin)){
        c = fgetc(fin);
        if (isalnum(c) && !isalnum(_c)){
            num++;
            sized = 0;
            curr_size = SIZE;
        }
        if (isalnum(c)){
            if (num == 1){
                if (sized == curr_size - 2){
                    buff1[sized] = '\0';
                    buff1 = str_realloc(buff1, curr_size*=2);
                }
                buff1[sized++] = c;
            }
            else if (num == 2){
                if (sized == curr_size - 2){
                    buff2[sized] = '\0';
                    buff2 = str_realloc(buff2, curr_size*=2);
                }
                buff2[sized++] = c;
            }
            else if (num == 3){
                if (sized == curr_size - 2){
                    buff3[sized] = '\0';
                    buff3 = str_realloc(buff3, curr_size*=2);
                }
                buff3[sized++] = c;
            }
        }
        else if (isalnum(_c) && !isalnum(c) && c != '\r' && c != EOF){
            if (num == 1){
                if (sized == curr_size - 2){
                    buff1[sized] = '\0';
                    buff1 = str_realloc(buff1, curr_size + 1);
                }
                buff1[sized] = '\0';
            }
            else if (num == 2){
                if (sized == curr_size - 2){
                    buff2[sized] = '\0';
                    buff2 = str_realloc(buff2, curr_size + 1);
                }
                buff2[sized] = '\0';
            }
            else if (num == 3){
                if (sized == curr_size - 2){
                    buff3[sized] = '\0';
                    buff3 = str_realloc(buff3, curr_size + 1);
                }
                buff1[sized] = '\0';
            }
        }
        else if (c == '\r' || c == EOF){
            fprintf(fout, "%s %s %s", buff3, buff1, buff2);
            c != EOF ? fputc('\r', fout) : fputc(' ', fout);
            free(buff1);
            free(buff2);
            free(buff3);
            if (c != EOF){
                buff1 = str_init(curr_size);
                buff2 = str_init(curr_size);
                buff3 = str_init(curr_size);
            }
            num = 0;
        }
        _c = c;
    }
    fclose(fin);
    fclose(fout);
    remove("f1.txt");
    rename("to_write_copy.txt", argv[1]);
    return 0;
}