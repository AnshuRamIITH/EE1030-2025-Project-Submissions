#include "matrixOps.h"
#include <string.h>
//this function dynamically allocates memory for new matrx 
matrix* make_matrix(int rows , int columns){
    matrix* mat =(matrix*)malloc(sizeof(matrix));

    mat -> rows = rows;//feeding data in matrix mat
    mat->cols=columns;

    mat->data=(double **)malloc(rows *sizeof(double*));//pointers help taken 
    //double ** is a way to stimulate 2D grid  
    for(int i=0;i<rows;i++){
        mat->data[i]=(double*)calloc(columns,sizeof(double));
    }
    return mat;
}

void free_matrix(matrix *m){
    if(!m) return;
    for(int i=0;i<m->rows;i++){
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

matrix* copy_matrix(matrix* m){

    matrix* n = make_matrix (m->rows, m->cols);

    for(int i=0; i< m-> rows ;i++){
        memcpy (n -> data[i],m ->data[i],m->cols * sizeof(double));
    }
    //memcpy(m1,m2,size);this copies all data from m2 to m1 ,
    //this copies data row wise so we give size multiplied by columns 

    return n;
}
void print_matrix(matrix* m,int size_d){
    int cols_d , rows_d;
    if(m->rows < size_d){
         rows_d=m->rows;
    }else{rows_d=size_d;}
    if(m->cols < size_d){
         cols_d=m->cols;
    }else{ cols_d=size_d;}
    

    printf("Matrix (%d X %d):\n",rows_d,cols_d);

    for(int i=0; i <rows_d ;i++){
        for(int j=0; j <cols_d; j++){
            printf("%8.4f ", m->data[i][j]);//8.4f makes 3.14 = 3.1400 , or normally 
        }
        if(m->cols>size_d) printf(". . .\n");
    }
    if(m->rows>size_d) printf(". . .\n");
}
matrix* mult_matrix(matrix* m,matrix* n){

    if(m->cols !=n->rows){ 
        fprintf(stderr," Incompatible Matrices for multiplication.\n");//stderr is used to print errors in files 
        exit(1);
    } 

    matrix* p = make_matrix(m->rows ,n->cols);

    for(int i=0 ; i<m->rows; i++){
        for(int j=0 ; j<n->cols ; j++){
            p ->data[i][j] = 0.0;
            for(int k=0 ; k<m->cols ; k++){
                p->data[i][j] += m->data[i][k] * n->data[k][j];
            }
        }
    }

    return p;

}

matrix* transpose(matrix * m){

    matrix* n = make_matrix(m->cols, m->rows);//taking cols=rows and vice cersa

    for(int i=0; i<m->rows ;i++){
        for(int j=0; j<m->cols ;j++){
            n->data[j][i]= m->data[i][j];
        }
    }

    return n;
}



double f_norm( matrix *m ) {
    double sum = 0.0;
    
    for (int i=0 ; i <m->rows; i++) {
        for (int j= 0; j  <m->cols; j++) {
            sum += m->data[i][j] * m-> data[i][j];
        }
    }
    //simply squaring every term and  
    return sqrt(sum);
}