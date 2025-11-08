#include "svd.h"
#include <string.h>

void power_iteration (matrix *A,double *eigenvalue,double *eigenvector,int max_iteration){
    int n= A->rows;
    //initialising vector to all ones 
    for(int i=0;i<n;i++){
        eigenvector[i]=1.0;
    }
    //main iteration loop
    for(int iteration=0;iteration<max_iteration;iteration++){
        //it will run maximum upto max iteration 
        double *temp =(double*)calloc(n,sizeof(double));

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){//eigenvalues are only defined for square matrices;
                temp[i]+=A->data[i][j]*eigenvector[j];
            }
        }
        //calculating the euclidean norm of temp 
        double norm=0.00;
        for(int i=0;i<n;i++){
            norm+=temp[i]*temp[i];
        }
        norm=sqrt(norm);
        //normalising the vector so that it does not overfolw(explote to infinity due to large eigenvalues )
        //or underflow (shrink towards zero)
        if(norm >=1e-12){//to avoid division by near 0;
            for(int i=0;i<n;i++){
            temp[i]/=norm ;
            }

        }
        double differ = 0.0;//differ is defined as the absolute sum ,
        // which will give us how much the vector has changed overall 
        for(int i=0;i<n;i++){
            differ+=fabs(temp[i]-eigenvector[i]);//fabs is nothing but mod gives + value of the diff
        }
        memcpy(eigenvector,temp,n*sizeof(double));
        //copying data from temp to eigenvector;
        free(temp);
        if(differ<1e-9) {
        
            break;}

    }//calculating eigenvalue
    //using rayleigh quotient: lamda=v^T *A*v 
    *eigenvalue =0.00;
    for(int i=0;i<n;i++){
        double sum=0.00;
        for(int j=0;j<n;j++){
            sum+=A->data[i][j]*eigenvector[j];
        }
        *eigenvalue+=eigenvector[i]*sum;
    }

}
void deflate_matrix(matrix *A,double eigenvalue, double *eigenvector){
        int n=A->rows;
        //remove the already extracted eigenpair , so that we dont have to rediscover same 
        //A=A-lamda*v*v^T
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                A->data[i][j]-=eigenvalue*eigenvector[i]*eigenvector[j];
            }
        }
}
//vomputing u for svd ;
matrix *get_u(matrix *A,matrix*V,double *sigma,int k){
    int m=A->rows;
    matrix *U=make_matrix(m,k);
    for(int i=0;i<k;i++){
        for(int row =0;row<m;row++){
            U->data[row][i] =0.0;//intislising 0;
            for(int cols=0;cols<A->cols;cols++){
                U->data[row][i]+=A->data[row][cols]*V->data[cols][i];
                //it is computing the dot product of row roth of A with ith column of V 
            }
            if(sigma[i]>1e-12){
                U->data[row][i]/=sigma[i];
            }

        }
    }
    return U;
}

SVD * compute_svd(matrix*A,int k,int max_iteration){
    printf("computing SVD uding power iteration with k=%d",k);

    matrix*AT=transpose(A);
    matrix*ATA =mult_matrix(AT,A);
    free_matrix(AT);

    int n=ATA->rows;
    double *eigenvalues =(double*)malloc(k*sizeof(double));
    matrix *V =make_matrix(n,k);

    //extracting k dominant eigenpairs 
    for(int i=0;i<k;i++){
        double eigenvector[n];
        //applying power iteration to find dominandt eigenpair
        power_iteration(ATA,&eigenvalues[i],eigenvector,max_iteration);
        //copying eigenvectro to v matrix 
        for(int j=0;j<n;j++){
            V->data[j][i]=eigenvector[j];
            
        }
        //removing current eigenpair fromATA so that we dont have repeat them
        if(i<k-1){
            deflate_matrix(ATA,eigenvalues[i],eigenvector);
        }

    }
    free_matrix (ATA);

    //converting eigenvalues to singular vakues sigma=sqrtof lamda
    double *sigma=(double*)malloc(k*sizeof(double));
    for(int i=0;i<k;i++){
        sigma[i ]=sqrt(fabs(eigenvalues[i]));
        //fabs os taking mod

    }
    matrix *U=get_u(A,V,sigma,k);

    SVD *result =(SVD*)malloc(sizeof(SVD));
    //here cast svd converts pointer  given by malloc to svd struct 
    result->U=U;
    result->sigma=sigma;
    result->V=V;
    result->k=k;
    free(eigenvalues);
    printf("SVD done , image is loading\n ");
    return result ;
    

}
matrix*reconstruct_image(SVD *svd){
    // using the new pixel value , we are constructing a new image 
    int k=svd->k;
    int m =svd->U->rows;
    int n =svd->V->rows;
    matrix*Ak=make_matrix(m,n);
    for(int rank=0;rank<k;rank++){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                Ak->data[i][j] 
                +=svd->sigma[rank]*svd->U->data[i][rank]*
                svd->V->data[j][rank];
            }
        }

    }
    return Ak;
}
void free_SVD(SVD *svd){
    if(!svd)return;
    if(svd->U)free_matrix(svd->U);
    if(svd->V)free_matrix(svd->V);
    if(svd->sigma)free(svd->sigma);
    free(svd);
}