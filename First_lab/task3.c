#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "ctype.h"


void no_num(FILE *fin, FILE *fout){
    int c;
    while ((c = fgetc(fin)) != EOF){
        if (!isdigit(c)){
            fputc(c, fout);
        }
    }
}


void count_symb(FILE *fin, FILE *fout){
    int c;
    int num = 0;
    while ((c = fgetc(fin)) != EOF){
        if (c != '\n' && isalpha(c)){
            num++;
        }
        else if(c == '\n'){
            fprintf(fout, "%d\n", num);
            num = 0;
        }
    }
}


void no_symb_ints(FILE *fin, FILE *fout){
    int c;
    int num = 0;
    while ((c = fgetc(fin)) != EOF){
        if (c != '\n' && !isalpha(c) && !isdigit(c) && c != ' '){
            num++;
        }
        else if (c == '\n'){
            fprintf(fout, "%ud\n", num);
            num = 0;
        }
    }
}


void ascii_ex(FILE *fin, FILE *fout){
    int c;
    while ((c = fgetc(fin)) != EOF){
        if (!isdigit(c)){
            fprintf(fout, "%d", (int)c);
        }
        else fputc(c, fout);
    }
}


void replace_two_five(FILE *fin, FILE* fout){
    int c, c_ = 0;
    int count = 1;
    while ((c = fgetc(fin)) != EOF){
        if ((isdigit(c) || isalpha(c)) &&(!isdigit(c_)&&!isalpha(c_))){
            count++;
            fputc(c, fout);
        }
        else if(!(count % 10)){
            c = tolower(c);
            isdigit(c) ? fprintf(fout, "%d", c) : fprintf(fout, "%d", tolower(c));
        }
        else if(!(count % 2) && isalpha(c)){
            fputc(tolower(c), fout);
        }
        else if(!(count % 5)){
            fprintf(fout, "%d", c);
        }
        else{
            fputc(c, fout);
        }
        c_ = c;
    }
}


int main(int argc, char *argv[]) {
    FILE* fin = NULL;
    FILE* fout = NULL;
    short int arlen = strlen(argv[1]);
    if (argc < 3 || arlen > 3){
        printf("Too few arguments, or incorrect input\n");
        exit(0);
    }
    fin = fopen(argv[2], "r");
    if (argv[1][1] == 'n'){
        if (argc != 4){
            printf("Too few arguments!\n");
            exit(0);
        }
        fout = fopen(argv[3], "w");
        if ((fin == NULL) || (fout == NULL)){
            printf("Wrong files, try another!\n");
            exit(0);
        }
        if (!strcmp(argv[1], "-nd") || !strcmp(argv[1], "/nd")){
            no_num(fin, fout);
        }
        else if (!strcmp(argv[1], "-ni") || !strcmp(argv[1], "/ni")){
            count_symb(fin, fout);
        }
        else if (!strcmp(argv[1], "-ns") || !strcmp(argv[1], "/ns")){
            no_symb_ints(fin, fout);
        }
        else if (!strcmp(argv[1], "-na") || !strcmp(argv[1], "/na")){
            ascii_ex(fin, fout);
        }
        else if (!strcmp(argv[1], "-nf") || !strcmp(argv[1], "/nf")){
            replace_two_five(fin, fout);
        }
    }
    char* out = "out_";
    char *st = calloc(4 + strlen(argv[2]) + 1, 1);
    strcat(st, out);
    strcat(st, argv[2]);
    fin = fopen(argv[2], "r");
    fout = fopen(argv[3], "w");
    if ((fin == NULL) || (fout == NULL)){
        printf("Wrong files, try another!\n");
        exit(0);
    }
    if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "/d")) {
        no_num(fin, fout);
    }
    else if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "/i")){
        count_symb(fin, fout);
    }
    else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "/s")){
        no_symb_ints(fin, fout);
    }
    else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "/a")){
        ascii_ex(fin, fout);
    }
    else if (!strcmp(argv[1], "-f") || !strcmp(argv[1], "/f")){
        replace_two_five(fin, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}