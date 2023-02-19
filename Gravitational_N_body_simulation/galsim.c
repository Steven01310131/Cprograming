#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

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


void main(int argc, char const *argv[]) {
    if( argc != 6 ){
    printf( "Wrong amount of inputs\n" );
    // return 1;
    }
    int N=atoi(argv[1]);                //Number of stars to simulate
    char *fileName = argv[2];   //filename 
    int nsteps=atoi(argv[3]);           // number of steps
    double delta_t=atof(argv[4]);            //timestep
    int graphics=atoi(argv[5]);
    double G=100.0/N;               //Gravitational constant 
    double r,rx,ry;         //registers to caclulate the the distance vectors


    star *stars = (struct star*)malloc(N *6* sizeof(double));
    FILE *file;
    file=fopen(fileName, "rb");
        fread(stars,N*6*sizeof(double),1,file);
    fclose(file);
    star_acc comp;
    comp.x  = malloc( N * sizeof(double) );
    comp.y  = malloc( N * sizeof(double) );
    comp.m  =malloc( N * sizeof(double));
    for(int i=0;i<N;i++){
        comp.x[i]=stars[i].x;
        comp.y[i]=stars[i].y;
        comp.m[i]=stars[i].m;
    }
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
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
        for(int i=0;i<N;i++)
        {
            comp.x[i]+=delta_t*stars[i].vx;
            comp.y[i]+=delta_t*stars[i].vy;
        }   
    }
    for(int i=0;i<N;i++){
        stars[i].x=comp.x[i];
        stars[i].y=comp.y[i];
        stars[i].m=comp.m[i];
    }


    FILE* fp2 = fopen( "result.gal","w");
    if(fp2 == NULL)
    {
        printf("The file was not created.\n");
        exit(EXIT_FAILURE);
    }
	
    fwrite(stars,(N*6*sizeof(double)),1,fp2); 
    fclose(fp2);

    free(stars);
    free(comp.x);
    free(comp.y);
    free(comp.m);
}
