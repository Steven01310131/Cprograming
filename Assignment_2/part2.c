/*Reading from the file little_bin_file which has the following data:
•An integer number represented using the datatype int
•A floating-point number represented using the datatype double
•A character represented using the datatype char
•A floating-point number represented using the datatype float
*/


#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *file;
    typedef struct 
    {
        int int_num;
        double db_num;
        char character;
        float fl_num;
        
    }data;
    data values;
    printf("%ld\n",sizeof(char));
    // values=malloc(sizeof(data));
    // values=(data_t*)malloc(sizeof(data_t));
 
    file=fopen("little_bin_file","rb");
    fread(&values,sizeof(values),17,file);
    printf("int number is %d\n", values.int_num);
    printf("int number is %f\n", values.db_num);
    printf("int number is %c\n", values.character);
    printf("int number is %f\n", values.fl_num);


    fclose(file);

    






}