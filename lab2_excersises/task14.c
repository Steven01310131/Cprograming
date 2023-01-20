#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>



int main(int argc,char const *argv[])
{
    FILE *in_file;
    char filename[50];
    char product[50];
    double price;
    strcpy(filename,argv[1]);
    in_file = fopen(filename, "r");
    fscanf(in_file,"%*s");
    while (fscanf(in_file, "%*s %s", product) != EOF) {
        printf("%s\n", product);
    }

    fclose(in_file);
    exit(EXIT_SUCCESS);
}
