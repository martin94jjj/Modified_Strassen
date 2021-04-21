# include <cstdio>
# include <cmath>
# include <iostream>
# include <string>
# include <ctime>
# include <iomanip>
# include <fstream>
#include "omp.h"

using namespace std; 

void mat_mul(const int* A, const int* B, int* C, int n)
{
    //computes A*B = C where A is m*n B is n*p and C is m*p
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int sum = 0;
            for (int k=0; k<n; k++) {
                sum += A[n*i+k] * B[n*k+j];
            }
            //stores c value into pointer
            C[n*i+j] = sum;
        }
    }
}
void mat_add(const int* A, const int* B, int*C, const int n){
    //addition for n*n matrices
    for(int i =0;i<n*n;i++){
        C[i] = A[i]+B[i];
    }
}
void mat_sub(const int* A, const int* B, int*C,  const int n){
    //addition for n*n matrices
    for(int i =0;i<n*n;i++){
        C[i] = A[i]-B[i];
    }
}

void print_submatrices(const int* A00, const int* A01, const int* A10, const int* A11, const int n, const int nNew, const int flag,char matrix){
    if(flag>10 && n>2){
        for(int j=0;j<nNew;j++){
            for(int k=0;k<nNew;k++){
                if(j==0 && k==0){
                    cout<<matrix;
                    printf("00\n");
                }
                printf("%d",A00[j*nNew+k]);
            }
            printf("\n");
        }
    }
    if(flag>10 && n>2){
        for(int j=0;j<nNew;j++){
            for(int k=0;k<nNew;k++){
                if(j==0 && k==0){
                    cout<<matrix;
                    printf("01\n");
                }
                printf("%d",A01[j*nNew+k]);
            }
            printf("\n");
        }
    }
    if(flag>10 && n>2){
        for(int j=0;j<nNew;j++){
            for(int k=0;k<nNew;k++){
                if(j==0 && k==0){
                    cout<<matrix;
                    printf("10\n");
                }
                printf("%d",A10[j*nNew+k]);
            }
            printf("\n");
        }
    }
    if(flag>10 && n>2){
        for(int j=0;j<nNew;j++){
            for(int k=0;k<nNew;k++){
                if(j==0 && k==0){
                    cout<<matrix;
                    printf("11\n");
                }
                printf("%d",A11[j*nNew+k]);
            }
            printf("\n");
        }
        printf("\n");
        //printf("%.2f\n",A11[0]);
    }
}

void strassens(const int* A, const int* B, int* C, const int n, const int flag,const int n0){

    int nNew;
    bool padded = false;

    //to be changed according to the best size of n
    if(n<=n0){
        mat_mul(A,B,C,n);
        return;
    }
    if(n%2!=0){
        nNew = (n+1)/2;
        padded = true;
    }
    else{
        nNew = n/2;
    }
    
    if(flag>10 && n>2){
        printf("n is %d, nNew is %d \n",n,nNew);
    }

    int* A00 = new int[nNew*nNew];
    int* A01 = new int[nNew*nNew];
    int* A10 = new int[nNew*nNew];
    int* A11 = new int[nNew*nNew];

    int* B00 = new int[nNew*nNew];
    int* B01 = new int[nNew*nNew];
    int* B10 = new int[nNew*nNew];
    int* B11 = new int[nNew*nNew];

    int* Q0 = new int[nNew*nNew];
    int* Q1 = new int[nNew*nNew];
    int* Q2 = new int[nNew*nNew];
    int* Q3 = new int[nNew*nNew];
    int* Q4 = new int[nNew*nNew];
    int* Q5 = new int[nNew*nNew];
    int* Q6 = new int[nNew*nNew];

    int* C00 = new int[nNew*nNew];
    int* C01 = new int[nNew*nNew];
    int* C10 = new int[nNew*nNew];
    int* C11 = new int[nNew*nNew];

    int* temp = new int[nNew*nNew];
    int* temp1 = new int[nNew*nNew];

    //assign values to the sub-matrices

    //store indices for relevant sub-matrices
    int index00 = 0;
    int index01 = 0;
    int index10 = 0;
    int index11 = 0;

    if(!padded){
        int i = 0;
        while(i<n){
            int j = 0;
            while(j<n){
                if(i<nNew){
                    if(j<nNew) {
                        A00[index00] = A[i*n+j];
                        B00[index00] = B[i*n+j];
                        index00++;
                    }
                    else{
                        A01[index01] = A[i*n+j];
                        B01[index01] = B[i*n+j];
                        index01++;
                    }
                }
                else{
                    if(j<nNew) {
                        A10[index10] = A[i*n+j];
                        B10[index10] = B[i*n+j];
                        index10++;
                    }
                    else{
                        A11[index11] = A[i*n+j];
                        B11[index11] = B[i*n+j];
                        index11++;
                    }
                }
                j++;
            }
            i++;
        }
    }
    else{
        //if padding is needed, we add padding to 01,10 and 11 sub-matrices
        int i = 0;
        while(i<n+1){
            int j = 0;
            while(j<n+1){
                if(i<nNew){
                    if(j<nNew){
                        A00[index00] = A[i*n+j];
                        B00[index00] = B[i*n+j];
                        index00++;
                    }
                    else{
                        if(j==n){
                            //pad 01 sub-matrices, right-most line with 0
                            A01[index01] = 0;
                            B01[index01] = 0;
                            index01++;
                        }
                        else{
                            A01[index01] = A[i*n+j];
                            B01[index01] = B[i*n+j];
                            index01++;
                        }
                    }
                }
                else if(i==n){
                    //pad the bottom line with 0
                    if(flag>10){
                        printf("i %d,j %d,val %d,index %d, assigned val %d\n",i,j,A[i*n+j],index11,A11[index11]);
                    }

                    if(j<nNew){
                        A10[index10] = 0;
                        B10[index10] = 0;
                        index10++;
                    }
                    else{
                        A11[index11] = 0;
                        B11[index11] = 0;
                        index11++;
                    }
                }
                else{
                    if(j<nNew){
                        A10[index10] = A[i*n+j];
                        B10[index10] = B[i*n+j];
                        index10++;
                    }
                    else{
                        if(j==n){
                            A11[index11] = 0;
                            B11[index11] = 0;
                            if(flag>10){
                                printf("i %d,j %d,val %d,index %d, assigned val %d\n",i,j,A[i*n+j],index11,A11[index11]);
                            }
                            index11++;
                        }
                        else{
                            A11[index11] = A[i*n+j];
                            B11[index11] = B[i*n+j];
                            if(flag>10){
                                printf("i %d,j %d,val %d,index %d, assigned val %d\n",i,j,A[i*n+j],index11,A11[index11]);
                            }                            
                            index11++;
                        }
                    }
                }
                if(flag>10){
                    printf("i %d,j %d, A11[0] value %d\n",i,j,A11[0]);
                }
                j++;
            }

            i++;

        }
    }

    print_submatrices(A00,A01,A10,A11,n,nNew,flag,'A');

    //calculate Q0
    mat_add(A00,A11,temp,nNew);
    mat_add(B00,B11,temp1,nNew);
    strassens(temp,temp1,Q0,nNew,flag,n0);
    //calculate Q1
    mat_add(A10,A11,temp,nNew);
    strassens(temp,B00,Q1,nNew,flag,n0);
    //calculate Q2
    mat_sub(B01,B11,temp,nNew);
    strassens(A00,temp,Q2,nNew,flag,n0);
    //calculate Q3
    mat_sub(B10,B00,temp,nNew);
    strassens(A11,temp,Q3,nNew,flag,n0);
    //calculate Q4
    mat_add(A00,A01,temp,nNew);
    strassens(temp,B11,Q4,nNew,flag,n0);
    //calculate Q5
    mat_sub(A10,A00,temp,nNew);
    mat_add(B00,B01,temp1,nNew);
    strassens(temp,temp1,Q5,nNew,flag,n0);
    //calculate Q6
    mat_sub(A01,A11,temp,nNew);
    mat_add(B10,B11,temp1,nNew);
    strassens(temp,temp1,Q6,nNew,flag,n0);
    //calculate C00
    mat_add(Q0,Q3,temp,nNew);
    mat_sub(temp,Q4,temp1,nNew);
    mat_add(temp1,Q6,C00,nNew);
    //calculate C10
    mat_add(Q1,Q3,C10,nNew);
    //calculate C01
    mat_add(Q2,Q4,C01,nNew);
    //calculate C11
    mat_add(Q0,Q2,temp,nNew);
    mat_sub(temp,Q1,temp1,nNew);
    mat_add(temp1,Q5,C11,nNew);

    print_submatrices(C00,C01,C10,C11,n,nNew,flag,'C');

    //assign value from submatrices to matrix C
    index00 = 0;
    index01 = 0;
    index10 = 0;
    index11 = 0;

    if(!padded){
        int i =0;
        while(i<n){
            int j = 0;
            while(j<n){
                if(i<n/2){
                    if(j<n/2){
                        C[i*n+j] = C00[index00];
                        index00++;
                    }
                    else{
                        C[i*n+j] = C01[index01];
                        index01++;
                    }
                }
                else{
                    if(j<n/2){
                        C[i*n+j] = C10[index10];
                        index10++;
                    }
                    else{
                        C[i*n+j] = C11[index11];
                        index11++;
                    } 
                }
                j++;
            }
            i++;
        }
    }
    else{
         //if submatrices are padded, then we need to remove pad when combining them in to C
        int i = 0;
        while(i<n+1){
            int j = 0;
            while(j<n+1){
                if(i<nNew){
                    if(j<nNew){
                        C[i*n+j] = C00[index00];
                        index00++;
                    }
                    else{
                        if(j==n){
                            //skip padding
                            index01++;

                        }
                        else{
                            C[i*n+j] = C01[index01];
                            index01++;
                        }
                    }
                }
                else if(i==n){
                    //pad the bottom line with 0

                    if(j<nNew){
                        //skip padding
                        index10++;
                    }
                    else{
                        //skip padding
                        index11++;
                    }
                }
                else{
                    if(j<nNew){
                        C[i*n+j] = C10[index10];
                        index10++;
                    }
                    else{
                        if(j==n){
                            //skip padding
                            index11++;
                        }
                        else{
                            C[i*n+j] = C11[index11];
                            index11++;
                        }
                    }
                }
                j++;
            }
            i++;
        }
    }
}



int main(int argc, char *argv[]){
    char *flag = argv[1];
    char *dimension = argv[2];
    char *input_file = argv[3];
    double strassen_seconds = 0;
    double mat_mul_seconds = 0;

    srand((unsigned) time (NULL));

    int flag_val =atoi(flag);
    //dimension
    int n = atoi(dimension);

    int* A = new int[n*n];
    int* B = new int[n*n];
    int* C = new int[n*n];

    if(flag_val==0){

        ifstream infile(input_file);

        int val;
        int counter = 0;
        while(infile>>val){
            if (counter<n*n){
                A[counter] = val;
            }
            else{
                B[counter-n*n] = val;
            }
            counter++;
        }
        strassens(A,B,C,n,flag_val,20);
        for(int i = 0; i<n;i++){
            printf("%d \n",C[i*n+i]);
        }
        printf("\n");
    }

    if(flag_val>=3 && flag_val<5){
        //calculate part 3
        float p[] = {0.01,0.02,0.03,0.04,0.05};
        int n0 = 30;
        printf("trial,p,num_triangle\n");
        for(int index=0;index<5;index++){
            for(int trial=0;trial<5;trial++){
                A = new int[n*n];
                printf("%d,",trial);
                for(int i = 0;i<n;i++){
                    for(int j=0;j<i;j++){
                        if(j!=i){
                            float rand_d = (float) rand()/ (RAND_MAX);
                            //printf("%.2f\n",rand_d);
                            if( rand_d <= p[index]){
                                A[i*n+j]=1;
                                A[j*n+i]=1;
                            }
                        }
                    }
                }
                //compute A^2
                strassens(A,A,B,n,flag_val,n0);
                //compute A^3
                strassens(A,B,C,n,flag_val,n0);
                int sum = 0;
                for(int i = 0; i<n;i++){
                    sum+=C[i*n+i];
                }
                printf("%.2f,%d \n",p[index],sum/6);

                if(flag_val==4){
                    for(int i = 0; i<n;i++){
                        for(int j=0;j<n;j++){
                            printf("%d ",A[i*n+j]);   
                        }
                        printf("\n");

                    }
                    printf("\n");
                }
            }
        }
    }

    if(flag_val>4 && flag_val<7){
        printf("n,n0,strassen,mat_mul\n");       
        for(int n0 = 15;n0<50;n0+=1){
            A = new int[n*n];
            B = new int[n*n];
            for(int i = 0; i<n;i++){
                for(int j = 0; j<n;j++){
                    float rand_d = (float) rand()/ (RAND_MAX);
                    if(rand_d>=0.5){
                        A[i*n+j] = 1;//some number to fill A
                    }
                    rand_d = (float) rand()/ (RAND_MAX);
                    if(rand_d>=0.5){
                        B[i*n+j] = 1;//some number to fill B
                    }
                }
            }
            float t0 = omp_get_wtime();
            strassens(A,B,C,n,flag_val,n0);
            float t1 = omp_get_wtime();
            strassen_seconds  = t1-t0;

            if(flag_val>5){
                for(int i = 0; i<10;i++){
                    printf("%d ",C[i*n+i]);
                }
                printf("\n");
            }

            t0 = omp_get_wtime();
            mat_mul(A, B, C, n);
            t1 = omp_get_wtime();
            mat_mul_seconds = t1-t0;

            if(flag_val>5){
                for(int i = 0; i<10;i++){
                    printf("%d ",C[i*n+i]);
                }
                printf("\n");
            }
            printf("%d,%d,%.2f,%.2f\n",n,n0,strassen_seconds,mat_mul_seconds);

        }
    }

    if(flag_val==7){
        printf("n,n0,mat_mul\n");       
        for(int n0 = 0;n0<100;n0=n0+2){
            A = new int[(n+n0)*(n+n0)];
            B = new int[(n+n0)*(n+n0)];
            for(int i = 0; i<n+n0;i++){
                for(int j = 0; j<n+n0;j++){
                    float rand_d = (float) rand()/ (RAND_MAX);
                    if(rand_d>=0.5){
                        A[i*(n+n0)+j] = 1;//some number to fill A
                    }
                    rand_d = (float) rand()/ (RAND_MAX);
                    if(rand_d>=0.5){
                        B[i*(n+n0)+j] = 1;//some number to fill B
                    }
                }
            }


            float t0 = omp_get_wtime();
            mat_mul(A, B, C, n+n0);
            float t1 = omp_get_wtime();
            mat_mul_seconds = t1-t0;


            printf("%d,%.2f\n",n+n0,mat_mul_seconds);

        }
    }
    //strassens(A,B,C,n,flag_val,37);

    //mat_mul(A,B,C,n);


}
