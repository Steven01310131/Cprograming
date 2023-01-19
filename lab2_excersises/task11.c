#include <stdio.h>
#include <stdlib.h>
int main(){
    int *arr;
    int i=0,n,m;
    arr=(int*)malloc(sizeof(int));
    printf("Enter your array\n");
    while(scanf("%d",&n)==1){
        arr[i]=n;
        i++;
        arr=realloc(arr,(i+1)*sizeof(int));
    }
    n=0;
    for (int j=0;j<i;j++){
        n+=arr[j];
    }
    printf("sum is %d \n",n);
    printf("i%d\n",i);
    for(int j=0;j<i;j++)
        printf("%d",arr[j]);
}