#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // open the file
    FILE *file = fopen("little_bin_file", "r");
    // check if the file was opened successfully
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // read the data from the file
    int i;
    double d;
    char c;
    float f;
    fread(&i, sizeof(int), 1, file);
    fread(&d, sizeof(double), 1, file);
    fread(&c, sizeof(char), 1, file);
    fread(&f, sizeof(float), 1, file);
    // close the file
    fclose(file);
    // print the data
    printf("Integer: %d\n", i);
    printf("Double: %f\n", d);
    printf("Char: %c\n", c);
    printf("Float: %f\n", f);

    // return 0 to indicate success
    return 0;
}
