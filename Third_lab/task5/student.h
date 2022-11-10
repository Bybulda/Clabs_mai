#ifndef STUDENT_H
#define STUDENT_H

typedef struct student{
  size_t id;
  char* name;
  char* surname;
  short course;
  short ex_grades[5];
  char* group;
}student;


typedef struct stud_node{
  struct stud_node* next;
  student* stud;
}stud_node;


int cmp_id(const void*, const void*);
int cmp_surname(const void*, const void*);
int cmp_name(const void*, const void*);
int cmp_group(const void*, const void*);
int print_to_con(student** stud);

#endif
