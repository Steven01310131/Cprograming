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
    fp = fopen("file.txt", "rb");
    while (count<N  ){
        fscanf(fp, "%lf%lf%lf%lf%lf%lf", &stars[count].x, &stars[count].y,&stars[count].m,
              &stars[count].vx,&stars[count].vy,&stars[count].brightness);
    }
    fclose(fp);


    for(int t=0;t<nsteps;t++){ // loop through all the time stepts
 
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    if(i!=j){
                        rx=stars[i].x-stars[j].x;
                        ry=stars[i].y-stars[j].y;
                        r=sqrt(rx*rx-ry*ry)+epsilon;
                        stars[i].Fx+=-G*stars[i].m*stars[j].m*rx/r*r*r;
                        stars[i].Fy+=-G*stars[i].m*stars[j].m*ry/r*r*r;
                        }
                    stars[i].ax=stars[i].Fx/stars[i].m;
                    stars[i].ay=stars[i].Fy/stars[i].m;
                    stars[i].vx+=delta_t*stars[i].ax;
                    stars[i].vy+=delta_t*stars[i].ay;

                }
                for(int j=0;j<N;j++){
                    stars[i].x+=delta_t*stars[i].vx;
                    stars[i].y+=delta_t*stars[i].vy;
                }
            }
    }

    return 0;

}