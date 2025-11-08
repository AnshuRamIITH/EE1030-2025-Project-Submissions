#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrixOps.h"
#include "svd.h"
#include "imageTake.h"
#include <math.h>

int main(int argc,char *argv[]){
    //reading argumnets , we are expecting 3 
    //input,output and executable file 
    const char *input_file =argv[1];
    const char *output_prefix=argv[2];
    printf("SVD Image Compression starting ....\n");
    printf("reaing input image \n");
    matrix*A=read_image(input_file);
    
    int k_values[]= {5,20,50,100};
    int num_k =4;
    int max_iteration =100;
    for(int i=0;i<num_k;i++){
        int k=k_values[i];
        
        int max_k = (A->rows < A->cols)?A->rows:A->cols;
        //////////////////////////////
        if(k>max_k){
            printf("k is too large%d\n",k);
            continue;
        }
        printf("processing k=%d\n",k);
        clock_t start =clock();
        SVD *svd = compute_svd(A, k, max_iteration);
        clock_t end=clock();
        double timetaken=((double)(end-start))/CLOCKS_PER_SEC;//gives time in seconds 
        matrix *Ak =reconstruct_image(svd);

        ///// error /////
        matrix *error_matrix =copy_matrix(A);
        for(int i=0;i<A->rows;i++){
            for(int j=0;j<A->cols;j++){
                error_matrix->data[i][j]-=Ak->data[i][j];
            }
        }
        double forbeniusError=f_norm(error_matrix);
        free_matrix(error_matrix);
        printf("Error ||A - A_k||_F= %.4f\n", forbeniusError);
        int original_size=A->rows *A->cols;
        int compressed_size =k *(A->rows + A->cols + 1);
        double compression_ratio  =(double)original_size / compressed_size;
        char output_filename[256];
        snprintf(output_filename, sizeof(output_filename), "%s_k%d.jpg", output_prefix, k);
        write_image(output_filename, Ak);
        //original size m*n;
        //reduced size km+kn+k;
        // it is actually the total no of pixel values stored 
        printf(" Compression ratio is  %.2fx\n", compression_ratio);
        printf("Time taken: %.3f s\n", timetaken);
        free_matrix(Ak);
        free_matrix(svd->U);
        free_matrix(svd->V);
        free(svd->sigma);
        free(svd);
        printf("\n");



    }

    printf("SVD Image Compression completed ....\n");
    free_matrix(A);
    return 0;
}