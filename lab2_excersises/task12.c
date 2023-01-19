#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int is_prime(int n);
int main(){
    int n,k=1,m=0;
    int *arr,*prime_arr;
    printf("enter a size of the array\n");
    scanf("%d",&n);
    // Initialize the arrays 
    arr=(int*)malloc(n*sizeof(int));
    prime_arr=(int*)malloc(sizeof(int));
    // fill the initial first array.
    for(int i=0;i<=n;i++){
        arr[i]=rand() % 100;
        printf("%d,",arr[i]);
        }
    // remove the primes from original array
    printf("\n");
    for(int i=0;i<n;i++){
        m=arr[i];
        if(is_prime(m)){
            
            prime_arr=realloc(prime_arr,k*sizeof(int));
            prime_arr[k]=arr[i];
            k++;
            
            for(int j=i;j<=n;j++){
                arr[j]=arr[j+1];
            }
        }
    }
    // for(int i=0;i<=n;i++){
    //     printf("%d,",arr[i]);
    //     } 
    // printf("\n");
    for(int i=0;i<=k-1;i++){
        printf("%d,",prime_arr[i]);
        } 

}
int is_prime(int n){
    for(int i=2;i<=n;i++){
        if(n%i==0) return 0;
        else return 1;
    }
}