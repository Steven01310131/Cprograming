#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}




int main(int argc, char const *argv[]){
    int N=atoi(argv[1]);
    double **A = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    
    double **L = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        L[i] = (double *)malloc(N * sizeof(double));
    }

    double **U = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        U[i] = (double *)malloc(N * sizeof(double));
    }
    double time1 = get_wall_seconds();
    for (int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=rand()%10;
            U[i][j]=A[i][j];
            L[i][j]=0; 
        }
    }
    
    for (int j=0;j<N;j++)
    {
        L[j][j]=1;
        double register temp=1/U[j][j];
        for(int i=j+1;i<N;i++)
        {
            
            L[i][j]=U[i][j]*temp;
            for(int k=0;k<N;k++)
            {
                U[i][k]=U[i][k]-L[i][j]*U[j][k];
            }
            
        }

    }
    printf("Simulating %7.5f wall seconds.\n", get_wall_seconds()-time1);

        double **LU = (double **)malloc(N * sizeof(double *));
for (int i = 0; i < N; i++) {
    LU[i] = (double *)malloc(N * sizeof(double));
}

for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        double sum = 0.0;
        for (int k = 0; k <= fmin(i, j); k++) {
            sum += L[i][k] * U[k][j];
        }
        LU[i][j] = sum;
    }
}
        double eps = 1e-6;  // Set a tolerance for floating-point comparisons
    int is_correct = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(A[i][j] - LU[i][j]) > eps) {
                is_correct = 0;
                break;
            }
        }
        if (!is_correct) {
            break;
        }
    }

    if (is_correct) {
        printf("LU decomposition is correct.\n");
    } else {
        printf("LU decomposition is incorrect.\n");
    }


    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);

    return 0;
}