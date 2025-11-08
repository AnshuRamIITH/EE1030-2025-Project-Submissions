#pragma once 
#include  <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int rows ;
    int cols ;
    double **data;
} matrix;
//defining name at last in struct enables us to not use the keyword matrix everywhere 

matrix *make_matrix(int rows, int cols);
void free_matrix(matrix* m);
matrix* copy_matrix(matrix *m);
void print_matrix(matrix* m, int size_d);

matrix* transpose (matrix* m);
matrix* mult_matrix(matrix *m,matrix * n); 

double f_norm(matrix *m);

