#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int i,number, checker=0;
    printf("enter number:");
    scanf("%d",&number);
    for(i=1;i<number;i++){
        if (number==i*i){
            checker=1;
        }
    }
    if(checker){
        printf("the number %d is a perfect square\n",number);
    }
    else{
        printf("the number %d is not a  perfect square\n",number);
    }
}