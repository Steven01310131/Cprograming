#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc,char const *argv[])
{
    typedef struct product
    {
    char name[50];
    double price;
    }
    product_t;
    FILE *in_file;

   

    char filename[50];
    int number_of_products;
    double temp_price;

    char temp_char[50];

    strcpy(filename,argv[1]);
    in_file = fopen(filename, "r");
    fscanf(in_file,"%d",&number_of_products);
    product_t arr_of_prod[number_of_products];
    int i=0;
    while (fscanf(in_file, "%s %lf",temp_char,&temp_price) != EOF) {
        strcpy(arr_of_prod[i].name,temp_char);
        arr_of_prod[i].price=temp_price;
        ++i;
    }

    for (int j=0;j<i;j++){
        printf("%s %lf\n",arr_of_prod[j].name,arr_of_prod[j].price);
    }
    fclose(in_file);
    return 0;
}