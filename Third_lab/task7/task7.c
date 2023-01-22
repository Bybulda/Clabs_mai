#include "task7.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int civ_init(civilian** civ){
  (*civ)->name = NULL;
  (*civ)->surname = NULL;
  (*civ)->patronymic = NULL;
  (*civ)->birth_date = NULL;
  (*civ)->sex = -1;
  (*civ)->salary = 0.0;
}

int list_init(civ_node** node){
  *node = (civ_node*)malloc(sizeof(civ_node));
  if (!*node){
    return NO_MEMORY;
  }
  (*node)->civ = (civilian*)malloc(sizeof(civilian));
  if(!(*node)->civ){
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
  char* b1 = (*el)->civ->birth_date;
  char* b2 = next->civ->birth_date;
  int count = 0;
  while (cmp_age(b1, b2) && next->next != NULL){
    next = next->next;
    b2 = next->civ->birth_date;
    count++;
  }
  if (count == 0){
    (*el)->next = next;
    *head = *el;
  }
  else if (!next->next){
    next->next = *el;
  }
  else{
    tmp = next->next;
    next->next = *el;
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
  char* buf = NULL, tmp;
  int len = 0, size = 2, posl = 0;
  char c = fgetc(fin);
  if(list_init(head) == NO_MEMORY){
    return NO_MEMORY;
  }
  civ_node* curr = NULL;
  civ_node* pred = *head;
  while(c != EOF){
    if (c == ' '){
      /**/
    }
    else if(c == '\n'){
      if (size == len){
        tmp = buf;
        tmp = (char*)realloc(buf, size+1);
        free(buf);
        if (!tmp){
          return NO_MEMORY;
        }
        buf = tmp;
      }
      buf[len] = '\0';
      curr->civ->salary = atof(buf);
      free(buf);
      pred->next = curr;
      pred = pred->next;
      curr = NULL;
      if (list_init(&curr) = NO_MEMORY){
        return NO_MEMORY;
      }
      buf = NULL;
      len = 0;
      size = 2;
      posl = 0;
    }
    else{
      if (size == len){
        tmp = buf;
        size<<=1;
        tmp = (char*)realloc(buf, size);
        free(buf);
        if (!tmp){
          return NO_MEMORY;
        }
        buf = tmp;
      }
      buf[len++] = c;
    }
    c = fgetc;
  }
}

int cmp_age(char* b1, char* b2){
  int flag = 0, num_b1 = 0, num_b2 = 0, equ = 0;
  int counter = 0
  char buff1[5] = {'', '', '', '', '\0'}, buff2[5] = {'', '', '', '', '\0'}
  for(int i = 9; i > 0; i--){
    if (b1[i] == '.' || b2[i] == '.'){
      buff1[counter] = '\0';
      buff2[counter] = '\0';
      num_b1 = atoi(buff1);
      num_b2 = atoi(buff2);
      if (num_b1 != num_b2){
        flag = num_b1 < num_b2;
        break;
      }
      counter = 0;
    }
    else{
      buff1[counter] = bf1[i];
      buff2[counter] = bf2[i];
      counter++;
    }
  }
  return flag;
}
