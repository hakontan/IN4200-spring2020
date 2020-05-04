#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "mpi_count_friends_of_ten.c"

int main (int argc, char **argv) {

    int M = 0, N = 0, rank, size, num_triple_friends=0;
    int **v=NULL;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if (rank==0) {
        srand (time(NULL));
        M = 100;
        N = 100;
        v = malloc(N * sizeof(double *));
        v[0] = malloc(N * M * sizeof(double));
    
        for (int i = 1; i < M; i ++) {
            v[i] = &v[0][M * i];
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++){
                v[i][j] = rand() % (9 + 1 - 0) + 0;
            }
        }

    num_triple_friends = mpi_count_friends_of_ten(M, N, v);
    }


    if (rank != 0) {
        num_triple_friends = mpi_count_friends_of_ten(0, 0, NULL);
    }

    printf("MPI rank <%d>: number of triple friends=%d\n",
            rank, size);
    
    MPI_Finalize ();

    if (rank==0) {
        free(v);
    }
    return 0;
}