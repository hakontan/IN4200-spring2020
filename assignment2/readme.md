## Build and run Instructions:
To compile the program run the included makefile. This will produce executable for the MPI implementation mpi_count.out and the serial implementation serial_count.out. The programs require c11 standard and MPI.
If you want to compile them separately this can be done as
* gcc serial_main.c -o serial_count.out -std=c11 -O3
* mpirun serial_main.c -o serial_count.out -std=c11 -O3
When running the programs remember to insert the matrix dimensions M and N as first and second command line argument respectively. In the utils.c file there is included an implementation of the example matrix given in the exam text. If you want to test the program on this matrix, replace int **v = allocate_2D_int(M, N); with int **v = example_array(); and send M=4 and N=5 as arguments through the command line