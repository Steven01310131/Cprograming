#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int a;
    int b;
    int c;

    printf("enter number a: \n");
    scanf("%d",&a);
    printf("enter number b: \n");
    scanf("%d",&b);
    if(a%2==0 & b%2==0){
        printf("Both numbers are even their sum is: %d\n",a+b);
    }
    else{
        printf("Both numbers are not even their product is %d \n",a*b);
    }


    printf("enter number a: \n");
    scanf("%d",&a);
    printf("enter number b: \n");
    scanf("%d",&b);
    printf("enter number c: \n");
    scanf("%d",&c);
    
    if(a*a>b*b){
        if (c*c>a*a){
            printf("the largest number is: %d",c);
        }
        else{
            printf("the largest number is: %d",a);
        }

    }
    if(b*b>a*a){
        if (c*c>b*b){
            printf("the largest number is: %d",c);
        }
        else{
            printf("the largest number is: %d",b);
        }

    }
    printf("\n");
    if(a*a>b*b){
        if (c*c>a*a){
            printf("the second largest number is: %d",a);
        }
        else{
            printf("the second largest number is: %d",c);
        }

    }
    if(b*b>a*a){
        if (c*c>b*b){
            printf("the second largest number is: %d",b);
        }
        else{
            printf("the second largest number is: %d",c);
        }

    }
    printf("\n");

    return 0;
}
