#include "task7.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int civ_init(civilian** civ){
  if (!*civ){
    return NO_MEMORY;
  }
  (*civ)->name = NULL;
  (*civ)->surname = NULL;
  (*civ)->patronymic = NULL;
  (*civ)->birth_date = NULL;
  (*civ)->sex = -1;
  (*civ)->salary = 0.0;
  return DONE;
}

int list_init(civ_node** node){
  *node = (civ_node*)malloc(sizeof(civ_node));
  if (!*node){
    return NO_MEMORY;
  }
  (*node)->civ = (civilian*)malloc(sizeof(civilian));
  if (civ_init(&((*node)->civ)) == NO_MEMORY){
    return NO_MEMORY;
  }
  (*node)->next = NULL;
  return DONE;
}

int del_civ(civilian** civ){
  free((*civ)->name);
  free((*civ)->surname);
  free((*civ)->patronymic);
  free((*civ)->birth_date);
  free(*civ);
  return DONE;
}

int list_destroy(civ_node** civ){
  civ_node* next = NULL;
  while (*civ){
    next = (*civ)->next;
    del_civ(&((*civ)->civ));
    free(*civ);
    *civ = next;
  }
  *civ = NULL;
  return DONE;
}

int node_del(civ_node** head, int pos, int size){
  int code = pos_el(size, pos);
  civ_node* next = *head;
  if (code == INPUT_ERROR)
    return INPUT_ERROR;
  if (code == 1){
    while(--pos != 1){
      next = next->next;
    }
    civ_node* create = next->next->next;
    del_civ(&(next->next->civ));
    free(next->next);
    next->next = create;
  }
  else if(code == -1){
    list_destroy(head);
  }
  else{
    while(--pos != 1){
      next = next->next;
    }
    del_civ(&(next->next->civ));
    free(next->next);
    next->next = NULL;
  }
  return DONE;
}

int node_add(civ_node** head, civ_node** el){
  civ_node* next = *head;
  civ_node* tmp = NULL;
  civ_node* pred = next;
  char* b1 = (*el)->civ->birth_date;
  char* b2 = NULL;
  int count = 0, code = -2;
  while (next != NULL){
    b2 = next->civ->birth_date;
    int res = cmp_age(b1, b2);
    if (res){
      break;
    }
    pred = next;
    next = next->next;
    count++;
  }
  if (count == 0){
    b2 = next->civ->birth_date;
    code = cmp_age(b1, b2);
    if (code){
      (*el)->next = next;
      *head = *el;
    }
    else{
      if (next->next){
        tmp = next->next;
        (*head)->next = *el;
        (*el)->next = tmp;
      }
      else{
        (*head)->next = *el;
      }
    }
    
  }
  else if (!next){
    pred->next = *el;
  }
  else{
    tmp = pred->next;
    pred->next = *el;
    (*el)->next = tmp;
  }
  return DONE;

}

int pos_el(int size, int pos){
  if (pos < 0 || pos > size)
    return INPUT_ERROR;
  if (pos < size && pos > 0)
    return 1;
  return (pos == size && size != 1) - 1;
}

int from_file_to_list(FILE* fin, civ_node** head){
  char* buf = NULL, *tmp;
  int len = 0, size = 2, posl = 0, size_of_list = 0;
  char c = fgetc(fin);
  if(list_init(head) == NO_MEMORY){
    return NO_MEMORY;
  }
  civ_node* curr = *head;
  civ_node* pred = *head;
  buf = (char*)malloc(size*sizeof(char));
  if (!buf)
    return NO_MEMORY;
  while(1){
    if (c == ' '){
      if (size == len)
      {
        tmp = buf;
        size += 1;
        tmp = (char *)realloc(buf, size);
        if (!tmp)
        {
          free(buf);
          return NO_MEMORY;
        }
        buf = tmp;
      }
      buf[len] = '\0';
      switch (posl)
      {
      case 0:
        curr->civ->name = buf;
        break;
      case 1:
        curr->civ->surname = buf;
        break;
      case 2:
        curr->civ->patronymic = buf;
        break;
      case 3:
        curr->civ->birth_date = buf;
        break;
      case 4:
        curr->civ->sex = buf[0] != 'M';
        free(buf);
        break;
      default:
        buf = NULL;
        break;
      }
      posl++;
      len = 0;
      size = 2;
      buf = (char *)malloc(size * sizeof(char));
      if (!buf)
        return NO_MEMORY;
    }
    else if(c == '\n' || c == EOF){
      if (size == len){
        tmp = buf;
        tmp = (char*)realloc(buf, size+1);
        
        if (!tmp){
          free(buf);
          return NO_MEMORY;
        }
        buf = tmp;
      }
      buf[len] = '\0';
      curr->civ->salary = atof(buf);
      free(buf);
      // pred->next = curr;
      // pred = pred->next;
      if (!size_of_list){
        *head = curr;
      }
      else{
        node_add(head, &curr);
      }
      curr = NULL;
      size_of_list++;
      if (c == EOF){
        break;
      }
      if (list_init(&curr) == NO_MEMORY){
        return NO_MEMORY;
      }
      len = 0;
      size = 2;
      posl = 0;
      buf = (char *)malloc(size * sizeof(char));
      if (!buf)
        return NO_MEMORY;
    }
    else{
      if (size == len){
        tmp = buf;
        size<<=1;
        tmp = (char*)realloc(buf, size);
        if (!tmp){
          free(buf);
          return NO_MEMORY;
        }
        buf = tmp;
      }
      buf[len++] = c;
    }
    c = fgetc(fin);
  }
}

int cmp_age(char* b1, char* b2){
  int flag = 1, num_b1 = 0, num_b2 = 0, equ = 0, curr_len = 5;
  int counter = 3;
  char* buff1 = (char*)malloc((curr_len) * sizeof(char));
  char* buff2 = (char*)malloc((curr_len) * sizeof(char));
  if (!buff1 || !buff2)
    return NO_MEMORY;
  for(int i = 9; i > -2; i--){
    if (b1[i] == '.' || b2[i] == '.' || i == -1){
      buff1[curr_len - 1] = '\0';
      buff2[curr_len - 1] = '\0';
      num_b1 = atoi(buff1);
      num_b2 = atoi(buff2);
      free(buff1);
      free(buff2);
      if (num_b1 != num_b2){
        flag = num_b1 > num_b2;
        break;
      }
      counter = 1;
      curr_len = 3;
      buff1 = (char*)malloc(3*sizeof(char));
      buff2 = (char*)malloc(3 * sizeof(char));
      if (!buff1 || !buff2)
        return NO_MEMORY;
    }
    else{
      buff1[counter] = b1[i];
      buff2[counter] = b2[i];
      counter--;
    }
  }
  return flag;
}

int from_list_to_file(FILE *fout, civ_node **head){
  civ_node* curr = *head;
  char sex = 0;
  while (curr){
    sex = curr->civ->sex == M ? 'M' : 'F';
    char *name = curr->civ->name, *surname = curr->civ->surname, *patronomic = curr->civ->patronymic, *birthday = curr->civ->birth_date; 
    float salary = curr->civ->salary;
    fprintf(fout, "%s %s %s %s %c %f\n", name, surname, patronomic, birthday, sex, salary);
    curr = curr->next;
  }
}

int insert(civ_node** head, char *name, char *surname, char *patronomic, char *birth_day, char sex, float salary){
  civ_node* curr;
  if(list_init(&curr) == NO_MEMORY)
    return NO_MEMORY;
  char* buff = NULL;
  buff = (char*)malloc((strlen(name) + 1)*sizeof(char));
  strcpy(buff, name);
  curr->civ->name = buff;
  buff = (char *)malloc((strlen(surname) + 1) * sizeof(char));
  strcpy(buff, surname);
  curr->civ->surname = buff;
  buff = (char *)malloc((strlen(patronomic) + 1) * sizeof(char));
  strcpy(buff, patronomic);
  curr->civ->patronymic = buff;
  buff = (char *)malloc((strlen(birth_day) + 1) * sizeof(char));
  strcpy(buff, birth_day);
  curr->civ->birth_date = buff;
  curr->civ->sex = (sex == 'M' ? M : F);
  curr->civ->salary = salary;
  return node_add(head, &curr);
}

int find(civ_node **head, char *name, char *surname, char *patronomic, char *birth_day, char sex, float salary){
  civ_node* tmp = *head;
  double eps = 1e-9;
  int flag = 0;
  do{
    if (name){
      if (strcmp(name, tmp->civ->name))
        continue;
    }
    if (surname){
      if (strcmp(surname, tmp->civ->surname))
        continue;
    }
    if (patronomic)
    {
      if (strcmp(patronomic, tmp->civ->patronymic))
        continue;
    }
    if (birth_day)
    {
      if (strcmp(birth_day, tmp->civ->birth_date))
        continue;
    }
    if (sex)
    {
      int code = sex != 'M'; 
      if (code != tmp->civ->sex)
        continue;
    }
    if (salary > 0.){
      if(fabs(tmp->civ->salary - salary) > eps)
        continue;
    }
    flag = 1;
    break;
  } while ((tmp = tmp->next));
  if (flag){
    sex = tmp->civ->sex == M ? 'M' : 'F';
    char *name = tmp->civ->name, *surname = tmp->civ->surname, *patronomic = tmp->civ->patronymic, *birthday = tmp->civ->birth_date;
    float salary = tmp->civ->salary;
    printf("%s %s %s %s %c %f\n", name, surname, patronomic, birthday, sex, salary);
  }
}