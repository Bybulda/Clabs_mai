#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


enum ERRORS{
  NO_MEMORY = -1,
  WRONG_INPUT = -2,
  BAD_OPERATION = -3,
  DONE = 0
};


typedef struct matrix{
    int** matr;
    int n;
    int m;
    double det;
}matrix;

void matrix_print(matrix* matr);
void fill_matrix(matrix** matr);
void destroy_matrix(matrix** matr);
int GaussDet(matrix** matr);
int create_matrix(matrix** matr);
int multiply_matrix(matrix** matr1, matrix** matr2, matrix** result);
int count_det(matrix** matr);



int main() {
    srand(time(NULL));
    matrix* matr1 = (matrix*)malloc(sizeof(matrix));
    matrix* matr2 = (matrix*)malloc(sizeof(matrix));
    matrix* res = (matrix*)malloc(sizeof(matrix));
    if (!(matr1&&matr2&&res)){
        printf("Sry np memorry for u\n");
        return NO_MEMORY;
    }
    if (create_matrix(&matr1) == NO_MEMORY){
        printf("Sorry bro, no memorry for first matrix!\n");
        return NO_MEMORY;
    }
    if (create_matrix(&matr2) == NO_MEMORY){
        printf("Sorry bro, no memorry the second!\n");
        return NO_MEMORY;
    }
    printf("\nSo, the first matrix looks like this:\n");
    matrix_print(matr1);
    printf("\nAnd the second matrix looks like this:\n");
    matrix_print(matr2);
    printf("\nThe result of multyplication:\n");
    switch(multiply_matrix(&matr1, &matr2, &res)){
        case DONE:
            break;
        case BAD_OPERATION:
            printf("Sorry, could not multiply matrix!\n");
            destroy_matrix(&matr1);
            destroy_matrix(&matr2);
            return BAD_OPERATION;
        case NO_MEMORY:
            printf("Sorry, no Memorry!\n");
            destroy_matrix(&matr1);
            destroy_matrix(&matr2);
            return NO_MEMORY;
    }
    matrix_print(res);
    destroy_matrix(&matr1);
    destroy_matrix(&matr2);
    if (GaussDet(&res) == BAD_OPERATION){
      printf("Could not find determinant!\n");
      destroy_matrix(&res);
      return BAD_OPERATION;
    }
    printf("Determinant of result matrix is %lf\n", res->det);
    destroy_matrix(&res);
    return 0;
}


void matrix_print(matrix* matr){
    int n = matr->n, m = matr->m;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", matr->matr[i][j]);
        }
        printf("\n");
    }
}


int create_matrix(matrix** matr){
    (*matr)->n = 3;
    (*matr)->m = 3;
    (*matr)->matr = (int**)malloc((*matr)->n*sizeof(int*));
    if (!(*matr)->matr){
        return NO_MEMORY;
    }
    for(int i = 0;i < (*matr)->n;i++){
        (*matr)->matr[i] = (int*)malloc((*matr)->m*sizeof(int));
        if (!(*matr)->matr[i]){
            return NO_MEMORY;
        }
    }
    fill_matrix(matr);
    return DONE;

}


void fill_matrix(matrix** matr){
    int n = (*matr)->n, m = (*matr)->m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            (*matr)->matr[i][j] = rand() % 201 - 100;
        }
    }
}


void destroy_matrix(matrix** matr){
    int n = (*matr)->n;
    for(int i = 0; i < n; i++){
        free((*matr)->matr[i]);
    }
    free((*matr)->matr);
    free(*matr);
}


int multiply_matrix(matrix** matr1, matrix** matr2, matrix** result){
    int n1 = (*matr1)->n, m1 = (*matr1)->m, n2 = (*matr2)->n, m2 = (*matr2)->m, res;
    if (m1 == n2){
        (*result)->n = n1;
        (*result)->m = m2;
        (*result)->matr = (int**)malloc(n1*sizeof(int*));
        if(!(*result)->matr){
            return NO_MEMORY;
        }
        for (int i = 0; i < n1; i++)
        {
            (*result)->matr[i] = (int*)malloc(m2*sizeof(int));
            if(!((*result)->matr[i])){
                return NO_MEMORY;
            }
        }
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                res = 0;
                for (int k = 0; k < m1; k++)
                {
                    res += (*matr1)->matr[i][k]*(*matr2)->matr[k][j];
                }
                (*result)->matr[i][j] = res;

            }

        }
        return DONE;
    }
    return BAD_OPERATION;
}

int GaussDet(matrix** matr){
  if ((*matr)->n != (*matr)->m)
    return BAD_OPERATION;
  int** m = (*matr)->matr;
  int n = (*matr)->n;
  double det = 1;
  for(int i = 0; i < n; ++i){
        double mx = fabs(m[i][i]);
        int idx = i;
        for(int j = i+1; j < n; ++j)
            if (mx < fabs(m[i][j])) mx = fabs(m[i][idx = j]);
        if (idx != i){
            for(int j = i; j < n; ++j){
                double t = m[j][i];
                m[j][i] = m[j][idx];
                m[j][idx] = t;
            }
            det = -det;
        }
        for(int k = i+1; k < n; ++k){
            double t = m[k][i]/m[i][i];

            for(int j = i; j < n; ++j)
                m[k][j] -= m[i][j]*t;
        }
    }
  for(int i = 0; i < n; ++i) det *= m[i][i];
  (*matr)->det = det;
  return DONE;
}
