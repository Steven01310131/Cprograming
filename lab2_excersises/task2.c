#include <stdio.h>
#include <stdlib.h>

int main(){ 
    int a;
    int b;
    int i;
    int j;

    printf("enter number a: \n");
    scanf("%d",&a);
    printf("enter number b: \n");
    scanf("%d",&b);
    for (i=a;i>0;i--){
        if(i==a || i==1){
            for(j=b;j>0;j--){
                printf("*");
            }       
        }
        else{
            for(j=b;j>0;j--){
                if(j==b || j==1){
                    printf("*");
                }
                else{
                    printf(".");
                }
            }            
        }
        printf("\n");
    }
    


}