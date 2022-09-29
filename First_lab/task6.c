#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int separator(int sep){
    if (sep == ' ' || sep == '\n' || sep == '\t'){
        return 1;
    }
    return 0;
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

int reversed_toi(char *s, int base, int size){
    int n = 0, index = size;
    int tmp = 1;
    while(index-- != 0){
        n += (isdigit(s[index]) ? (s[index] - '0') : (tolower(s[index]) - 'a' + 10)) * tmp;
        tmp *= base;
    }
    return n;
}


int main(int argc, char *argv[]) {
    FILE* fin = NULL;
    FILE* fout = NULL;
    if (!(fin = fopen(argv[1], "r")) && !(fout = fopen("buf.txt", "w"))){
        printf("File cant be opened, try again!\n");
    }
    int base = 2, c, _c = 0, sized = 0, sized_curr = 16, num;
    char* buff = str_init(sized_curr);;
    while ((c = fgetc(fin)) != EOF){
        if (isalnum(c)){
            if (sized == sized_curr - 2){
                buff[sized] = '\0';
                buff = str_realloc(buff, sized_curr*=2);
            }
            if (isdigit(c)){
                if (base < c - '0'){
                    base = c - '0' + 1;
                }
            }
            else{
                if (base < tolower(c) - 'a' + 10){
                    base = tolower(c) - 'a' + 11;
                }
            }
            buff[sized++] = c;
        }
        else if(isalnum(_c) && separator(c)){
            if (sized == sized_curr - 2){
                buff[sized] = '\0';
                buff = str_realloc(buff, sized_curr + 1);
            }
            buff[sized] = '\0';
            num = reversed_toi(buff, base, sized);
            fprintf(fout, "%s %d %d\n", buff, base, num);
            free(buff);
            base = 2;
            sized_curr = 16;
            sized = 0;
            buff = str_init(sized_curr);
        }
        _c = c;
    }
    return 0;
}
