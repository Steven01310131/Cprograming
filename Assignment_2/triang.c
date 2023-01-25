/* C program which prints Pascal’s triangle
                                            */

#include <stdio.h>
#include <stdlib.h>



int main(int argc,char const *argv[]){
    if( argc == 2 ) {
        int n=atoi(argv[1]); // converting the input argument into an int
        int matrix[n][n];    // statically allocated two-dimensional arrays
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if(j==i){
                    matrix[i][j]=1;
                    printf("%d",matrix[i][j]);
                    printf(" ");
                    break;
                }
                else if(j==0){
                    matrix[i][j]=1;
                    printf("%d",matrix[i][j]);
                    printf(" ");
                    
                }
                else{
                    matrix[i][j]=matrix[i-1][j-1]+matrix[i-1][j];
                    printf("%d",matrix[i][j]);
                    printf(" ");
                }
                
            }
            printf("\n");
        }
    }
    else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}