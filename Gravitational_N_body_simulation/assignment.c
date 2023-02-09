#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// struct for data that will be on the files
typedef struct star
{
    double x, y;
    double m;
    double vx, vy;
    double brightness;

}star;
typedef struct {
    double ax,ay;

} vector;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

void printStruct(struct star stars) // helper funtion too error check 
{

    printf("%e\n",stars.x);
    // printf("%e\n %e\n %e\n %e\n %e\n %e\n",stars.x,stars.y,stars.m,stars.vx,stars.vy,stars.brightness);
}
// Global functions
double N;
int nsteps;
char *fileName ;
double  delta_t;
struct star *stars;

void simulate1();
void simulate();
void simulate2();

int main(int argc, char *argv[]) {
    N=atof(argv[1]);                //Number of stars to simulate
    fileName = strdup( argv[2] );   //filename 
    nsteps=atoi(argv[3]);           // number of steps
    delta_t=atof(argv[4]);            //timestep
    

    double time1 = get_wall_seconds();


    simulate1();


    printf("Brute force Simulating %7.5f wall seconds.\n", get_wall_seconds()-time1);  

}




void simulate(){
    const double epsilon=1e-3;          // force modification
    const double G=100/N;               //Gravitational constant 
    
    double r,rx,ry,Fx,Fy,ax,ay;         //registers to caclulate the the distance vectors


    stars = (struct star*)malloc(N * sizeof(star));
    FILE *fp;
    fp = fopen(fileName, "rb");
    fread(stars,6*sizeof(double), N, fp);
    fclose(fp);
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
        for(int i=0;i<N;i++)
        {
            Fx=0;
            Fy=0;

            for(int j=0;j<N;j++)
            {
                if(i!=j)// checker so as to prevent the computaions for the particle to do on itself
                {  
                    rx=stars[i].x-stars[j].x;
                    ry=stars[i].y-stars[j].y;
                    r=sqrt(rx*rx+ry*ry)+epsilon;
                    Fx+=(-G*stars[i].m*stars[j].m*rx)/(r*r*r);
                    Fy+=(-G*stars[i].m*stars[j].m*ry)/(r*r*r);
                }
            }
            
            ax=Fx/stars[i].m;
            ay=Fy/stars[i].m;
            stars[i].vx+=delta_t*ax;
            stars[i].vy+=delta_t*ay;
        }
        for(int i=0;i<N;i++)
        {
            stars[i].x=stars[i].x+delta_t*stars[i].vx;
            stars[i].y=stars[i].y+delta_t*stars[i].vy;
        }   
        // printStruct(stars[0]);
    }


    FILE* fp2 = fopen( "results.gal", "w+b" );
    fwrite(stars,6*sizeof(double),N,fp);   
    fclose(fp2);
    free(stars);

}

void simulate1(){
    double epsilon=1e-3;          // force modification
    double G=100/N;               //Gravitational constant 
    
    double r,rx,ry;         //registers to caclulate the the distance vectors


    stars = (struct star*)malloc(N * sizeof(star));
    FILE *fp;
    fp = fopen(fileName, "rb");
    fread(stars,N*6*sizeof(double), 1, fp);
    fclose(fp);
    for(int n=0;n<nsteps;n++)// loop through all the time stepts
    { 
 
        for(int i=0;i<N;i++)
        {
            double denominator;
            vector a={0.0 , 0.0};
            for(int j=0;j<N;j++)
            {
                if(i!=j)// checker so as to prevent the computaions for the particle to do on itself
                {  
                    rx=stars[i].x-stars[j].x;
                    ry=stars[i].y-stars[j].y;
                    r=sqrt(rx*rx+ry*ry);
                    denominator=1/(r+epsilon)*(r+epsilon)*(r+epsilon);
                    a.ax+=(-G*(stars[j].m)*rx)*denominator;
                    a.ay+=(-G*(stars[j].m)*ry)*denominator;
                }
            }
            
            stars[i].vx+=delta_t*a.ax;
            stars[i].vy+=delta_t*a.ax;
        }
        for(int i=0;i<N;i++)
        {
            stars[i].x+=delta_t*stars[i].vx;
            stars[i].y+=delta_t*stars[i].vy;
        }   

    }


    FILE* fp2 = fopen( "results.gal", "w+b" );
    fwrite(stars,N*6*sizeof(double),1,fp);   
    fclose(fp2);
    free(stars);

}

void simulate2(){
    double epsilon=1e-3;          // force modification
    double G=100/N;               //Gravitational constant 
    
    double r,rx,ry;         //registers to caclulate the the distance vectors


    stars = (struct star*)malloc(N * sizeof(star));
    FILE *fp;
    fp = fopen(fileName, "rb");
    fread(stars,N*6*sizeof(double), 1, fp);
    fclose(fp);
    int b=N;
    double (* restrict Fx)[b] = malloc(sizeof(double[b][b]));
    double (* restrict Fy)[b] = malloc(sizeof(double[b][b]));
    
    for(int n;n<=nsteps;n++)// loop through all the time stepts
    { 
        for(int i=0;i<N;i++){
            double denominator;
            for(int j=0;j<i;j++)
            {       
                    
                    rx=stars[i].x-stars[j].x;
                    ry=stars[i].y-stars[j].y;
                    r=sqrt(rx*rx+ry*ry);
                    denominator=1/(r+epsilon)*(r+epsilon)*(r+epsilon);
                    Fx[i][j]=(-G*(stars[j].m)*rx)*denominator;
                    Fx[j][i]=-Fx[i][j];
                    Fy[j][i]=(-G*(stars[j].m)*ry)*denominator;
                    Fy[j][i]= -Fy[i][j];
            }
        }
        for(int i=0;i<N;i++)
        {
            vector a={0.0 , 0.0};
            for(int j=0;j<N;j++)
            { 
                if(i!=j)
                {
                a.ax+=Fx[i][j];
                a.ay+=Fy[i][j];
                }
           }
            stars[i].vx+=delta_t*a.ax;
            stars[i].vy+=delta_t*a.ax;
        }
        for(int i=0;i<N;i++)
        {
            stars[i].x+=delta_t*stars[i].vx;
            stars[i].y+=delta_t*stars[i].vy;
        }   

    }


    FILE* fp2 = fopen( "results.gal", "w+b" );
    fwrite(stars,N*6*sizeof(double),1,fp);   
    fclose(fp2);
    free(stars);

}