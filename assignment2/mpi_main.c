#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "utils.c"
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
        // Allocating v_array to be sent into counting
        // function and be distributed to all processes.
        int** v = allocate_2D_int(M, N);
        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++){
                v[i][j] = rand() % (9 + 1 - 0) + 0;
            }
        }

    num_triple_friends = mpi_count_friends_of_ten(M, N, v);

    free(v[0]);
    free(v);
    }


    if (rank != 0) {
        num_triple_friends = mpi_count_friends_of_ten(0, 0, NULL);
    }

    printf("MPI rank <%d>: number of triple friends=%d\n",
            rank, num_triple_friends);
    MPI_Barrier(MPI_COMM_WORLD);


    int tot_num_triple_friends = 0;
    MPI_Reduce(&num_triple_friends, &tot_num_triple_friends,
                size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0) {
        printf("Total number of triple friends=%d\n",
                tot_num_triple_friends);
    }
    MPI_Finalize ();

    return 0;
}