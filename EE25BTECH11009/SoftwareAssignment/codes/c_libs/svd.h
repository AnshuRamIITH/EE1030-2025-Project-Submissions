#pragma once
#include "matrixOps.h"
typedef struct{
    matrix* U;
    double* sigma;
    matrix* V;
    int k;

} SVD;

SVD* compute_svd( matrix *A, int k, int max_iter);
void power_iteration( matrix *A, double *eigenvalue, double *eigenvector, int max_iter);
void deflate_matrix( matrix *A, double eigenvalue, double *eigenvector);
matrix* get_u( matrix *A, matrix *V, double *sigma, int k );
matrix* reconstruct_image( SVD *svd );