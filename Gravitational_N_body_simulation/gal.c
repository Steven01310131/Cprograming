#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

typedef struct particle
{
	double x;
	double y;
	double m;
	double ux;
	double uy;
	double br;
} particle_t;

static double get_wall_seconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
	return seconds;
}

void main(int argc, char const *argv[])
{
	if (argc != 6)
	{
		printf("Incorrect number of arguments\n");
		printf("Supply in order: N, filename, nsteps, dt, graphics \n");
		return;
	}

	int N = atoi(argv[1]);
	char *filename = argv[2];
	int nsteps = atoi(argv[3]);
	double dt = atof(argv[4]); // Should be 1E-5
	dt = 1E-5;
	int graphics = atoi(argv[5]);
	double G = 100.0 / N;
	double eps0 = 1E-3;
	double T = nsteps * dt; // Final time of evolution
	double time;

	// Allocate memory
	particle_t *particles = (struct particle_t *)malloc(N * 6 * sizeof(double)); // Stores up to about 6500 particles in cache on my device.
	// Reading inputs
	FILE *file;
	file = fopen(filename, "rb");
	fread(particles, N * 6 * sizeof(double), 1, file);
	fclose(file);

	time = get_wall_seconds();

	// Time evolution
	for (double t; t <= T; t += dt)
	{ // Evolve time

		// printf("t=%lf\n",t);
		for (int i = 0; i < N; i++)
		{ // For setting acceleration of ith particle
			double ax = 0.0, ay = 0.0, rij, denom, C;
			for (int j = 0; j < N; j++) // Interaction by jth particle
			{
				// sqrt instead of sqrtf
				rij = sqrt((particles[i].x - particles[j].x) * (particles[i].x - particles[j].x) + (particles[i].y - particles[j].y) * (particles[i].y - particles[j].y));
				denom = 1 / ((rij + eps0) * (rij + eps0) * (rij + eps0));
				C = (-G * (particles[j].m) * denom);

				ax += C * (particles[i].x - particles[j].x);
				ay += C * (particles[i].y - particles[j].y);
			}

			particles[i].ux += ax * dt;
			particles[i].uy += ay * dt;
		}

		for (int i = 0; i < N; i++)
		{

			particles[i].x += particles[i].ux * dt;
			particles[i].y += particles[i].uy * dt;
		}
	}
	printf("galaxy simulation took %7.3f wall seconds.\n", get_wall_seconds() - time);

	// Save into a file
	FILE *fp = fopen("results.gal", "w"); // should be result.gal
	if (fp == NULL)
	{
		printf("The file was not created.\n");
		exit(EXIT_FAILURE);
	}

	fwrite(particles, (N * 6 * sizeof(double)), 1, fp);

	fclose(fp);
}
