#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

// struct for data that will be on the files
typedef struct star
{
    double x;
    double y;
    double m;
    double vx;
    double vy;
    double brightness;

}star;
typedef struct
{
    double x, y;
} vector;


typedef struct star_acc
{
    double *x;
    double *y;
    double *m;
}star_acc;
// global variables
int N;
int nsteps;
double delta_t;
double G;
star* stars; //making our array global so it can be accesed by the threads
star_acc comp;

void* calc_velocity(){
    double r,rx,ry;         //registers to caclulate the the distance vectors
    for(int i=0;i<N;i++){
        comp.x[i]=stars[i].x;
        comp.y[i]=stars[i].y;
        comp.m[i]=stars[i].m;
    }

 
        for(int i=0;i<N;i++)
        {

            vector a={0,0};
            double denominator;
            for(int j=0;j<i;j++)
            {
                    rx=comp.x[i]-comp.x[j];
                    ry=comp.y[i]-comp.y[j];
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    a.x+=(-G*comp.m[j]*rx)*denominator;
                    a.y+=(-G*comp.m[j]*ry)*denominator;
            }
            for(int j=i+1;j<N;j++){
                    rx=comp.x[i]-comp.x[j];
                    ry=comp.y[i]-comp.y[j];
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    a.x+=(-G*comp.m[j]*rx)*denominator;
                    a.y+=(-G*comp.m[j]*ry)*denominator;
            }
            stars[i].vx+=delta_t*a.x;
            stars[i].vy+=delta_t*a.y;
        }


}
void positions(){

        for(int i=0;i<N;i++)
        {
            stars[i].x+=delta_t*stars[i].vx;
            stars[i].y+=delta_t*stars[i].vy;
        }   
    
}

void main(int argc, char const *argv[]) {
    if( argc != 6 ){
    printf( "Wrong amount of inputs\n" );
     exit(EXIT_FAILURE);
    }
    N=atoi(argv[1]);                //Number of stars to simulate
    char *fileName = argv[2];       //filename 
    nsteps=atoi(argv[3]);           // number of steps
    delta_t=atof(argv[4]);          //timestep
    int graphics=atoi(argv[5]);
    G=100.0/N;                      //Gravitational constant 
    pthread_t thread[4];            // number of threads
    comp.x  = malloc( N * sizeof(double) );
    comp.y  = malloc( N * sizeof(double) );
    comp.m  =malloc( N * sizeof(double));
    stars = (struct star*)malloc(N *6* sizeof(double)); // allocate memory for an array of structs 
    
    
    FILE *file;                                  // File reading procedure 
    file=fopen(fileName, "rb");                  // and reading the data into our array 
        fread(stars,N*6*sizeof(double),1,file);  // of structs
    fclose(file);                                //
    
    
    for(int n=0;n<nsteps;n++)        // loop through all the time stepts
    { 
        calc_velocity();        // caclute the vx and vy in the current step
        positions();            //calculate the x and y   
    }
    FILE* fp2 = fopen( "result.gal","w");       // Create a new result.gal file  
    if(fp2 == NULL)                             // in which we will enter our data                   
    {                                           //    
        printf("The file was not created.\n");  //
        exit(EXIT_FAILURE);                     //
    }
	fwrite(stars,(N*6*sizeof(double)),1,fp2);   //
    fclose(fp2);                                //

    free(stars); // freeing the allocated memory for our struct
    free(comp.x);
    free(comp.y);
    free(comp.m);
}   