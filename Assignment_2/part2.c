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
//     typedef struct values {
//         int int_num;
//         double db_num;
//         char character;
//         float fl_num;
// } values;
        int int_num;
        double db_num;
        char character;
        float fl_num;

    // values values_read;
    //  printf("%ld\n",sizeof(values_read));
    // values=malloc(sizeof(data));
    // values=(data_t*)malloc(sizeof(data_t));
 
    file=fopen("little_bin_file","r");
    // fread(&values_read,sizeof(values_read),1,file);
    // printf("int number is %d\n", values_read.int_num);
    // printf("float number is %f\n", values_read.db_num);
    fread(&int_num,sizeof(int),1,file);
    fread(&db_num,sizeof(double),1,file);
    fread(&character,sizeof(char),1,file);
    fread(&fl_num,sizeof(float),1,file);

    printf("int number is %d\n", int_num);
    printf("int number is %f\n", db_num);
    printf("int number is %c\n", character);
    printf("int number is %f\n", fl_num);


    fclose(file);

    






}