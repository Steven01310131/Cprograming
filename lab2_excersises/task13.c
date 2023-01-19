#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>



int main()
{   const char* filename = "data.txt";
    FILE *in_file = fopen(filename, "r");

    struct stat sb;


    char *file_contents = malloc(sb.st_size);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        printf("%s\n", file_contents);
    }

    fclose(in_file);
    exit(EXIT_SUCCESS);
}
