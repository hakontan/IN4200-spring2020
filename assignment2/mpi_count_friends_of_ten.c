#include <stdio.h>


int mpi_count_friends_of_ten(int M, int N ,int **v) {
     int rank, size;
     int M_per_process, N_per_process;
     int M_rest, N_rest;

     MPI_Comm_size (MPI_COMM_WORLD, &size);
     MPI_Comm_rank (MPI_COMM_WORLD, &rank);

     if (rank == 0) {
          M_per_process = M / size;
          N_per_process = N / size;
          M_rest = M % size;
          N_rest = N % size;

          int len[2] = {M_per_process, N_per_process};
          printf("%i", v[0][0]);
          for (int i=1; i<size; i++){
               MPI_Send(&M_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
               MPI_Send(&N_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

               MPI_Datatype subarray;

               int start[2] = {0, (i-1) * M_per_process};
               int subsize[2] = {N, M_per_process};
               int original_size[2] = {N, M};
               MPI_Type_create_subarray(2, original_size, subsize, start,
                                        MPI_ORDER_C, MPI_INT, &subarray);
               MPI_Type_commit(&subarray);
               MPI_Send(&(v[0][0]), 1, subarray, i, 0, MPI_COMM_WORLD);

          }
          printf("rank %i v[0][0]=%i\n", rank, M_per_process);
          return 0;
     }

     if (rank > 0) {   
          MPI_Recv(&M_per_process, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Recv(&N_per_process, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          
          int **subarray = malloc(N * sizeof(double *));
          subarray[0] = calloc(N * M_per_process, sizeof(double));


          MPI_Recv(&(subarray[0][0]), N * M_per_process, MPI_INT,
                   0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          
          printf("rank %i v[0][0]=%i\n", rank, M_per_process);
          return 0;
     }

}