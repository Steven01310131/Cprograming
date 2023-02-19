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
    double r,rx,ry;     //registers to caclulate the the distance vectors


    star *stars = (struct star*)malloc(N *6* sizeof(double));
    FILE *fp;
    fp = fopen(fileName, "rb");
        fread(stars,6*sizeof(double), N, fp);
    fclose(fp);
    double (* restrict Fx)[N] = malloc(sizeof(double[N][N]));
    double (* restrict Fy)[N] = malloc(sizeof(double[N][N]));

    double time1 = get_wall_seconds();
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
        for(int i=0;i<N;i++)
        {

 
            double denominator;
            for(int j=0;j<i;j++)
            {
                rx=stars[i].x-stars[j].x;
                ry=stars[i].y-stars[j].y;
                r=sqrt((rx*rx)+(ry*ry))+1e-3;
                denominator=1.0/(r*r*r);
                Fx[i][j]=(-G*stars[j].m*rx)*denominator;
                Fx[j][i]=-Fx[i][j];
                Fy[i][j]=(-G*stars[j].m*ry)*denominator;
                Fy[j][i]=-Fy[i][j];
            
            }

        }
        for( int i = 0; i < N; ++i )
        {
            register double ax=0;
            register double ay=0;
            for( int j = 0; j < i; ++j )
            {
                ax += Fx[i][j];
                ay += Fy[i][j];
            }

            for( int j = i+1; j < N; ++j )              
            {
                ax += Fx[i][j];
                ay += Fy[i][j];
            }

            // Speed.
            stars[i].vx+=delta_t*ax;
            stars[i].vy+=delta_t*ay;
        }
        for(int i=0;i<N;i++)
        {
            stars[i].x+=delta_t*stars[i].vx;
            stars[i].y+=delta_t*stars[i].vy;
        }   

    }
    printf("Simulating %7.5f wall seconds.\n", get_wall_seconds()-time1);

    FILE* fp2 = fopen( "results.gal", "w+b" );
     

	fwrite(stars,N*6*sizeof(double),1,fp); 
    fclose(fp2);
    free(stars);
    free(fileName);
    return 1;
}