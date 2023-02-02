#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    double rx,ry;

 } vector;

typedef struct star {
    double x,y; // positions
    double ax,ay; // acceleration
    double vx,vy; // velocity
    double m; //mass
    double Fx,Fy; //total force exertion
    double brightness;
} star ;

int main(int argc, char *argv[]) {
    int N=atoi(argv[1]);                //Number of stars to simulate
    char *fileName = strdup( argv[2] ); //filename 
    int nsteps=atoi(argv[3]);           // number of steps
    double const delta_t=atoi(argv[4]); //timestep
    const float epsilon=0.001;          // force modification
    const double G=100/N;               //Gravitational constant 
    double r,rx,ry;                     //registers to caclulate the the distance vectors
    
    
    struct star stars[N];
    // struct star *stars = (struct star*)malloc(N * sizeof(star));      THIS DOESNT WORK WHEN I DYNAMICALLY ALLOCATE MEMORY
    // if (stars == NULL) {
    //     printf("Error allocating memory");
    //     return 1;
    // }
    // printf("%ld\n",sizeof(star));
    //stars=(struct star*) malloc(100000 * sizeof(struct star));
    /*for reading the initial conditions*/
    int count=0;
    
    FILE *fp;
    fp = fopen(fileName, "rb");
    while (count<N  ){
        
        fscanf(fp, "%lf %lf %lf %lf %lf %lf", &stars[count].x, &stars[count].y,&stars[count].m,&stars[count].vx,&stars[count].vy,&stars[count].brightness);
        count ++;
    }
    
    fclose(fp);
    for(int i=0;i<N;i++){
        printf("%d\t%e\n %e\t\n %e\t\n %e\t\n %e\t\n %e\t\n",i,stars[i].x,stars[i].y,stars[i].m,stars[i].vx,stars[i].vy,stars[i].brightness);
    }
    
}