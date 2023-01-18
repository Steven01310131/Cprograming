#include <stdio.h>
#include <stdlib.h>
void swap_nums(int* num1,int* num2);
void swap_pointers(char** num1,char** num2);
int main()
{
int a,b;
char *s1,*s2;
a = 3; b=4;
swap_nums(&a,&b);
printf("a=%d, b=%d\n", a, b);
s1 = "second"; s2 = "first";
swap_pointers(&s1,&s2);
printf("s1=%s, s2=%s\n", s1, s2);
return 0;
}

void swap_nums(int* num1,int* num2){
    int temp1,temp2;
    temp1=*num1;
    temp2=*num2;
    *num2=temp1;
    *num1=temp2;
}
void swap_pointers(char** num1,char** num2){
    char *temp1,*temp2;
    temp1=*num1;
    temp2=*num2;
    *num2=temp1;
    *num1=temp2;
}
