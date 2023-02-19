#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

typedef struct star_acc
{
    double *x;
    double *y;
    double *m;
    double *vx;
    double *vy;
}star_acc;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main(int argc, char *argv[]) {
    int N=atoi(argv[1]);                //Number of stars to simulate
    char *fileName = strdup( argv[2] );   //filename 
    int nsteps=atoi(argv[3]);           // number of steps
    double delta_t=atof(argv[4]);            //timestep
    double G=100.0/N;               //Gravitational constant 
    double r,rx,ry,ax,ay;         //registers to caclulate the the distance vectors


    star *stars = (struct star*)malloc(N *6* sizeof(double));
    FILE *fp;
    fp = fopen(fileName, "rb");
        fread(stars,6*sizeof(double), N, fp);
    fclose(fp);
    star_acc comp;
    comp.x  = malloc( N * sizeof(double) );
    comp.y  = malloc( N * sizeof(double) );
    comp.m  =malloc( N * sizeof(double));
    comp.vx  = malloc( N * sizeof(double) );
    comp.vy  =malloc( N * sizeof(double));
    double time1 = get_wall_seconds();
    for(int i=0;i<N;i++){
        comp.x[i]=stars[i].x;
        comp.y[i]=stars[i].y;
        comp.m[i]=stars[i].m;
        comp.vx[i]=stars[i].vx;
        comp.vy[i]=stars[i].vy;

    }
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
        for(int i=0;i<N;i++)
        {

            register double ax=0;
            register double ay=0;
            double denominator;
            for(int j=0;j<i;j++)
            {

                
                
                    rx=comp.x[i]-comp.x[j];
                    ry=comp.y[i]-comp.y[j];
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    ax+=(-G*comp.m[j]*rx)*denominator;
                    ay+=(-G*comp.m[j]*ry)*denominator;

                
            }
            for(int j=i+1;j<N;j++){

                    rx=comp.x[i]-comp.x[j];
                    ry=comp.y[i]-comp.y[j];
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    ax+=(-G*comp.m[j]*rx)*denominator;
                    ay+=(-G*comp.m[j]*ry)*denominator;


            }
            
            comp.vx[i]+=delta_t*ax;
            comp.vy[i]+=delta_t*ay;
        }
        for(int i=0;i<N;i++)
        {
            comp.x[i]+=delta_t*comp.vx[i];
            comp.y[i]+=delta_t*comp.vy[i];
        }   

    }
    for(int i=0;i<N;i++){
        stars[i].x=comp.x[i];
        stars[i].y=comp.y[i];
        stars[i].m=comp.m[i];
        stars[i].vy=comp.vx[i];
        stars[i].vx=comp.vy[i];
    }

    printf("Simulating %7.5f wall seconds.\n", get_wall_seconds()-time1);

    FILE* fp2 = fopen( "results.gal", "w+b" );
     

	fwrite(stars,N*6*sizeof(double),1,fp); 
    fclose(fp2);
    free(stars);
    free(fileName);
    return 1;
}