#ifndef TASK7_H
#define TASK7_H
#include <stdio.h>


enum ERRORS {
    NO_MEMORY = -1,
    INPUT_ERROR = -2,
    DONE = 0,
    FILE_ERROR = -3,
    HANDLED = -4
};

enum SEX{
  M = 0,
  F = 1
};

typedef struct civilian{
  char* surname;
  char* name;
  char* patronymic;
  char* birth_date;
  short sex;
  float salary;
}civilian;


typedef struct civ_node{
  struct civ_node* next;
  civilian* civ;
}civ_node;

int pos_el(int size, int pos);
int cmp_age(char* b1, char* b2);
int civ_init(civilian** civ);
int list_init(civ_node** head);
int del_civ(civilian** civ);
int list_destroy(civ_node** head);
int node_del(civ_node** head, int pos, int size);
int node_add(civ_node** head, civ_node** el);
int insert(civ_node **head, char *name, char *surname, char *patronomic, char *birth_day, char sex, float salary); 
int from_file_to_list(FILE *fin, civ_node **head);
int from_list_to_file(FILE* fout, civ_node** head);
int find(civ_node **head, char *name, char *surname, char *patronomic, char *birth_day, char sex, float salary);
int del_particular(civ_node **head, char *name, char *surname, char *patronomic, char *birth_day, char sex, float salary);

#endif
