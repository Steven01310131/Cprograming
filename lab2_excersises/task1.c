#include <stdio.h>
#include <stdlib.h>

int main(){ 
    int i;
    for(i=100;i>=0;i=i-4){
        if(i>0){ 
            printf("%d,",i);
            }
        else{
            printf("%d",i);
            }
    }
    printf("\n");
    i=100;
    while(i>=0){
        if(i>0){ 
            printf("%d,",i);
            }
        else{
            printf("%d",i);
            }
        i=i-4;
    }
    printf("\n");
    i=100;
    do{
        if(i>0){ 
            printf("%d,",i);
            }
        else{
            printf("%d",i);
            }
        i=i-4;
    }while(i>=0);
    printf("\n");
}
