#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void print_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", A[i][j]);
        }
        printf("\n");
    }
}
static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main(int argc, char const *argv[]) {
    int N=atoi(argv[1]);
    double **A = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
    }
    

    // initialize A with random values

    double **L = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        L[i] = (double *)malloc(N * sizeof(double));
    }

    double **U = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        U[i] = (double *)malloc(N * sizeof(double));
    }
double time1 = get_wall_seconds();
    // Perform LU decomposition
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
    }

    
 for(int j=0; j<N; j++)
    {
        for(int i=0; i<N; i++)
        {
            if(i<=j)
            {
                U[i][j]=A[i][j];
                for(int k=0; k<=i-1; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else
            {
                L[i][j]=A[i][j];
                for(int k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
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
    // free memory
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