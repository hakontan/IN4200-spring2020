#include <stdio.h>


int mpi_count_subarray(int M, int N ,int **v) {
    /*
    Program that counts friends of ten for each subarray.
    Identical to serial count_friends_of_ten.c except that
    it has to take into consideration the splitting into
    subarrays when counting the vertical part along the N-dimension.
    */
    int sum = 0;
    int nr_friends = 0;
    int size; int rank;

    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Checking horizontal axis
            if (j < N - 2) {
                for (int k = 0; k < 3; k++) {
                    sum += v[i][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
            //Checking vertical axis
            if (rank != 0) {
                // If rank does not count end of original matrix,
                // make sure it doesn't count the vertical part
                // of the overlap.
                if ((i < M - 2) && (j < N - 2)) {
                    for (int k = 0; k < 3; k++) {
                        sum += v[i + k][j];
                    }
                    if (sum == 10) {
                        nr_friends += 1;
                    }
                    sum = 0;
                }
            }
            if (rank == 0) {
                // If rank counts end of the matrix it counts
                // all indices to the end.
                if ((i < M - 2)) {
                    for (int k = 0; k < 3; k++) {
                        sum += v[i + k][j];
                    }
                    if (sum == 10) {
                        nr_friends += 1;
                    }
                    sum = 0;
                }
            }
            //Checking diagonal axis from left to right
            if ((i < M - 2) && (j < N - 2)) {
                for (int k = 0; k < 3; k++) {
                    sum += v[i + k][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }

            //checking diagonal axis from right to left
            if ((j >= 2) && (i < M - 2)) {
                for (int k = 0; k > -3; k--) {
                    sum += v[i - k][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
        }
    }
    return nr_friends;
}