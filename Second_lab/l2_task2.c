#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int len(char* str){
    int count = 0;
    while(*str++){
        count++;
    }
    return count;
}


int reverse(char* str){
    int ln = len(str);
    char* copy = str;
    char * pre = str + ln - 1;
    while (copy < pre){
        char buff = *copy;
        *copy = *pre;
        *pre = buff;
        *copy++;
        *pre--;
    }
    return 0;
}


int to_upper(char* str){
    int i = 0;
    while(*str++){
        if (!(i++ & 1))
            *str = (char) toupper(str[i]);
    }
    return 0;
}


int hard_func(char* str, int size){
    char *digit = calloc(size, sizeof(char));
    char *alpha = calloc(size, sizeof(char));
    char *els = calloc(size, sizeof(char));
    if (!digit || !alpha || !els){
        printf("No memory error\n");
        return -1;
    }
    int dis = 0, als = 0, elss = 0;
    for(int i = 0; i < size; i++){
      if (isdigit(str[i])){
        digit[dis++] = str[i];
      }
      else if(isalpha(str[i])){
        alpha[als++] = str[i];
      }
      else
        els[elss++] = str[i];
    }
    int cnt = 0;
    for(int i = 0; i < dis; i++)
      str[cnt++] = digit[i];
    for(int i = 0; i < als; i++)
      str[cnt++] = alpha[i];
    for(int i = 0; i < elss; i++)
        str[cnt++] = els[i];
    free(els);
    free(alpha);
    free(digit);
    return 0;
}


int str_cat(char* str1, char* str2, char* buff){
    char* tmp1 = str1;
    char* tmp2 = str2;
    char* tmp3 = buff;
    while(*tmp1){
        *tmp3++ = *tmp1++;
    }
    while(*tmp2){
        *tmp3++ = *tmp2++;
    }
    *tmp3 = '\0';
    return 0;
}


int main(int argc, char* argv[]){
    if (argc < 2 || argc > 4){
        printf("Wrong input!\n");
    }
    else if(!strcmp(argv[2], "-l")){
        printf("Current len of '%s' is: %d", argv[1], len(argv[1]));
    }
    else if(!strcmp(argv[2], "-r")){
        printf("The string before reverse: %s\n", argv[1]);
        reverse(argv[1]);
        printf("The string after reverse: %s\n", argv[1]);
    }
    else if(!strcmp(argv[2], "-u")){
        printf("The string before upper: %s\n", argv[1]);
        to_upper(argv[1]);
        printf("The string after upper: %s\n", argv[1]);
    }
    else if(!strcmp(argv[2], "-n")){
        printf("The formation of '%s' is ", argv[1]);
        hard_func(argv[1], len(argv[1]));
        printf("'%s'\n", argv[1]);
    }
    else if(!strcmp(argv[3], "-c")){
        printf("The first string - %s\n", argv[1]);
        printf("The second string - %s\n", argv[1]);
        char* buff = calloc((len(argv[1]) + len(argv[2]) + 1), sizeof(char));
        str_cat(argv[1], argv[2], buff);
        printf("The combined string - %s\n", buff);
        free(buff);
    }
    return 0;
}
