#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <time.h>

#define CIR_R 1 // Radius of circle 
#define SQUARE_BND (double)CIR_R / sqrt(2.0) // square boundary


// Compute the value of M, which is the number of darts lands in square out of circle
int dboard(int n);

// Gen random number between 0 and 1
double gen_random(void);

int main(int argc, char** argv) {

    // Parallel
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 0, R = 0;       // N is the number of darts simulated per round, R is number of round
    int collective_m = 0;   // Used by master, to collect sum of m from other processors each iteration
    int global_m = 0;       // Sum of all collective m
    double approx_pi = 0;   // Target value 

    // Rand seed
    srand(time(NULL) + rank);

    // Master (rank = 0) gets arguments
    if(rank == 0){
        if(argc != 3){
            printf("Please pass 2 args: number of darts (N) and number of rounds (R) \n");
            return 1;
        }

        char *p1, *p2;
    
        errno = 0;
        long N_long = strtol(argv[1], &p1, 10);
        long R_long = strtol(argv[2], &p2, 10);

        // Check the inputs are valid numbers
        if (errno != 0 || *p1 != '\0' || *p2 != '\0' 
                || N_long > INT_MAX || R_long > INT_MAX) {
            printf("Please pass in two valid numbers \n");
            return 1;
        } else {
            // No error
            N = N_long;
            R = R_long;    
        }        
    }

    // Broadcast N and R to all other processors, wait until every one receive
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&R, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
	
	// Timer start
    double start = MPI_Wtime();

    // N may not be divisible to p, hence + 1 if rank is samller than N % p
    int num_iter = N / size;
    if(rank < (N % size)){
        num_iter++;
    }

    // Compute M out of N in each processor
    for(int i = 0; i < R; i++){
        int local_m = dboard(num_iter);
        MPI_Reduce(&local_m, &collective_m, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        
        // collective_m will be overwritten in each round
        if(rank == 0){
            global_m += collective_m;
        }
    }

    // Compute PI 
    if(rank == 0){
        double avg_m = (double)global_m / R; 
        approx_pi = 2.0 * N / avg_m;		
    }

    // End timer
    MPI_Barrier(MPI_COMM_WORLD);
    double end = MPI_Wtime();
    MPI_Finalize();

    // Write output to file
    if(rank == 0) {
    	printf("N=%d, R=%d, P=%d, PI=%lf\nTime=%lf\n", N, R, size, approx_pi, end-start);
    }

    return 0;
}

int dboard(int n){
    int m = 0; // number of darts in square
    double r = 0.0, theta = 0.0, x = 0.0, y = 0.0;
    for(int i = 0; i < n; i++){
        // Rand gen darts in circle with radius 
        r = CIR_R * sqrt(gen_random());
        theta = gen_random() * 2 * M_PI;
        
        // 0 is the center of circle
        x = 0 + r * cos(theta);
        y = 0 + r * sin(theta);

        if(SQUARE_BND - fabs(x) < 0 || SQUARE_BND - fabs(y) < 0){
            continue;
        }
        m++;
    }
    return m;
}

double gen_random(){
    return (double) rand()/ ((double)RAND_MAX + 1); // +1 to exclude 1.0 edge case (on circumf of circle)
}
