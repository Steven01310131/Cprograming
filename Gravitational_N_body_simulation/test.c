#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    double rx,ry;

 } vector;

typedef struct star
{
    double x, y;
    double m;
    double vx, vy;
    double brightness;

}star;
void printStruct(struct star stars) // helper funtion too error check 
{

    printf("%e\n",stars.x);
    // printf("%e\n %e\n %e\n %e\n %e\n %e\n",stars.x,stars.y,stars.m,stars.vx,stars.vy,stars.brightness);
}
int main(int argc, char *argv[]) {
    int N=atoi(argv[1]);                //Number of stars to simulate
    // /char *fileName = strdup( argv[2] ); //filename 
    // int nsteps=atoi(argv[3]);           // number of steps
    // double const delta_t=atoi(argv[4]); //timestep
    // const float epsilon=0.001;          // force modification
    // const double G=100/N;               //Gravitational constant 
    // double r,rx,ry;                     //registers to caclulate the the distance vectors
    
    struct star *stars = (struct star*)malloc(N * sizeof(star));
    // struct acc * acc=(struct acc*)malloc(N * sizeof(acc));
    FILE *fp;
    fp = fopen("ellipse_N_00010_after200steps.gal", "rb");
    fread(stars,6*sizeof(double), N, fp);
    fclose(fp);
        for(int i=0;i<N;i++){
        
        printStruct(stars[i]);
    }
}