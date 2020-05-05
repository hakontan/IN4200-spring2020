
#include "count_friends_of_ten.c" 

int mpi_count_friends_of_ten(int M, int N ,int **v) {
     /*
     Program that splits the input matrix v along the N-axis
     and divides the matrix among all MPI processes before
     counting friends of ten.
     */

     int rank, size;
     int M_per_process, N_per_process;
     int M_rest, N_rest;
     int friends_of_ten;

     MPI_Comm_size (MPI_COMM_WORLD, &size);
     MPI_Comm_rank (MPI_COMM_WORLD, &rank);

     if (rank == 0) {
          // Dividing dimensions by size to calculate 
          // the size for each process.
          M_per_process = M / size;
          N_per_process = N / size;

          // Calculating rest as one process may have to do extra work
          // depending on M and N.
          M_rest = M % size;
          N_rest = N % size;

          //allocates subarray for process 0
          int **subarray_0 = allocate_2D_int(M, N_per_process + N_rest);

          // Filling subarray for process 0 with remaining values
          // in addition to a remainder if N % size != 0.
          for (int i = 0; i < M; i++) {
               for (int j = 0; j < N_per_process + N_rest; j++) {
                    subarray_0[i][j] = v[i][j + (size-1)*N_per_process];
               }
          }
          
          for (int i=1; i<size; i++){
               //Send information to other process
               MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
               MPI_Send(&N_per_process, 1, MPI_INT, i, 1, MPI_COMM_WORLD);

               // Splitting v array into subarray
               // and distributing to the other processes
               MPI_Datatype subarray;

               int start[2] = {0, (i-1) * (N_per_process)};
               // Need two extra along N dimension so that we count 
               // the whole intented part of the matrix.
               int subsize[2] = {M, (N_per_process + 2)}; 
               int original_size[2] = {M, N};

               MPI_Type_create_subarray(2, original_size, subsize, start,
                                        MPI_ORDER_C, MPI_INT, &subarray);
               MPI_Type_commit(&subarray);
               MPI_Send(&(v[0][0]), 1, subarray, i, 2, MPI_COMM_WORLD);
               
          }
          friends_of_ten = count_friends_of_ten(M, N_per_process + N_rest, subarray_0);

          free(subarray_0[0]);
          free(subarray_0);
          return friends_of_ten;
     }

     if (rank > 0) {   
          MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Recv(&N_per_process, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          
          //Allocating memory for recieving the subarray from root process
          int **subarray = allocate_2D_int(M, N_per_process + 2);

          
          MPI_Recv(&(subarray[0][0]), M * (N_per_process + 2), MPI_INT,
                   0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          friends_of_ten = count_friends_of_ten(M, N_per_process + 2, subarray);

          free(subarray[0]);
          free(subarray);
          return friends_of_ten;
     }

}