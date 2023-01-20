#include <stdio.h>
#include <stdlib.h>

int main(){
    double number1, number2, result;
    char operation;     

    printf("enter the first number ");
    scanf("%lf " ,&number1);
    printf("enter the second number ");
    scanf("%lf " ,&number2);

    printf("enter operand ");
    scanf("%c " ,&operation);

    switch (operation){
    case '/':
        result=number1/number2;
        break;
    case '-':
        result=number1-number2;
        break;
    case '=':
        result=number1+number2;
        break;
    case '*':
        result=number1*number2;
        break;
    
    default:
        printf("fail\n");
        break;
    }
    printf("the result is: %lf \n",result);
}