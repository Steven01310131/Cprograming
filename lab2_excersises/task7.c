#include <stdio.h>
#include <stdlib.h>
int main() {
    int input,remainder,reversed=0,original;
    printf("enter a number");
    scanf("%d",&input);
    original=input;
    while(input !=0){
        remainder=input%10;
        printf("asdasd %d\n",remainder);
        reversed=reversed*10+remainder;
        input/=10;
    }

    if (original==reversed){
        printf("the number is a palindrome\n");
    }
    else{
        printf("the number is not a palindrome\n");   
    }
}