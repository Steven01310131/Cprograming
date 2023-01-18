#include <stdio.h>
#include <stdlib.h>
int main() {
double number1=5.5555;
int number2=6;
char character='s';
printf("For the int\n");
printf("the value is %d its adress is %p and the size is %zu bytes\n",number2,&number2,sizeof(number2));
printf("For the double\n");
printf("the value is %lf its adress is %p and the size is %zu bytes\n",number1,&number1,sizeof(number1));
printf("For the character\n");
printf("the value is %c its adress is %p and the size is %zu bytes\n",character,&character,sizeof(character));



}