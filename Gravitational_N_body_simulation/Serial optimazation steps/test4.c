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
    double x;
    double y;
    double m;
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
    star_acc *comp= (struct star_acc*)malloc(N *3* sizeof(double));
    double time1 = get_wall_seconds();
    for(int i=0;i<N;i++){
        comp[i].x=stars[i].x;
        comp[i].y=stars[i].y;
        comp[i].m=stars[i].m;

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
                    rx=comp[i].x-comp[j].x;
                    ry=comp[i].y-comp[j].y;
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    ax+=(-G*comp[j].m*rx)*denominator;
                    ay+=(-G*comp[j].m*ry)*denominator;     
            }
            for(int j=i+1;j<N;j++){

                    rx=comp[i].x-comp[j].x;
                    ry=comp[i].y-comp[j].y;
                    r=sqrt((rx*rx)+(ry*ry))+1e-3;
                    denominator=1.0/(r*r*r);
                    ax+=(-G*comp[j].m*rx)*denominator;
                    ay+=(-G*comp[j].m*ry)*denominator;
            }
            
            stars[i].vx+=delta_t*ax;
            stars[i].vy+=delta_t*ay;
        }
        for(int i=0;i<N;i++)
        {
            comp[i].x+=delta_t*stars[i].vx;
            comp[i].y+=delta_t*stars[i].vy;
        }   

    }
    for(int i=0;i<N;i++){
        stars[i].x=comp[i].x;
        stars[i].y=comp[i].y;
        stars[i].m=comp[i].m;
    }

    printf("Simulating %7.5f wall seconds.\n", get_wall_seconds()-time1);

    FILE* fp2 = fopen( "results.gal", "w+b" );
     

	fwrite(stars,N*6*sizeof(double),1,fp); 
    fclose(fp2);
    free(stars);
    free(fileName);
    return 1;
}