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
    char *fileName =argv[2];   //filename 
    int nsteps=atoi(argv[3]);           // number of steps 
    double delta_t=atof(argv[4]);            //timestep


    const double epsilon=1e-3;          // force modification
    double G=100.0/N;               //Gravitational constant 
    
    double r,rx,ry,ax,ay;         //registers to caclulate the the distance vectors
    double data[6*N];

    // star *stars = (struct star*)malloc(N *6* sizeof(double));
    FILE *fp;
    fp = fopen(fileName, "rb");
    // for(int i=0;i<N;i++){
        fread(data,sizeof(double), N*6, fp);
    // }
    fclose(fp);
    star *stars=(star*)data;

    double time1 = get_wall_seconds();
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
        for(int i=0;i<N;i++)
        {

            ax=0;
            ay=0;
            for(int j=0;j<N;j++)
            {
                if(j!=i){
                    rx=stars[i].x-stars[j].x;
                    ry=stars[i].y-stars[j].y;
                    r=sqrt(rx*rx+ry*ry)+epsilon;
                    ax+=(-G*stars[j].m*rx)/(r*r*r);
                    ay+=(-G*stars[j].m*ry)/(r*r*r);
                }
            }
            
            stars[i].vx+=delta_t*ax;
            stars[i].vy+=delta_t*ay;
        }
        for(int i=0;i<N;i++)
        {
            stars[i].x+=delta_t*stars[i].vx;
            stars[i].y+=delta_t*stars[i].vy;
        }   

    }
    printf("%7.5f \n", get_wall_seconds()-time1);

    FILE* fp2 = fopen( "results.gal", "w+b" );
     

	fwrite(stars,N*6*sizeof(double),1,fp); 
    fclose(fp2);
    // free(stars);
    return 1;
}