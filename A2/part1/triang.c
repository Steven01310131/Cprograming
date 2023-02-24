#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // store the number of rows
    int rows = atoi(argv[1]);
    // allocate memory for the previous and current rows
    int *prev = malloc(sizeof(int) * rows);
    int *curr = malloc(sizeof(int) * rows);
    // loop through the rows
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j <= i; j++)
        {
            // inline if statement to check if we are at the beginning or end of the row
            // if we are, then the value is 1
            // otherwise, the value is the sum of the previous row's values at the current index and the previous index
            curr[j] = (j == 0 || j == i) ? 1 : prev[j - 1] + prev[j];

            // print the current value
            printf("%d ", curr[j]);
        }
        printf(" \n");
        // copy the current row to the previous row for the next iteration of the loop
        memcpy(prev, curr, sizeof(int) * rows);
    }
    // free the memory allocated for the rows
    free(prev);
    free(curr);

    // return 0 to indicate success
    return 0;
}
