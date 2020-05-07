int** allocate_2D_int(int Nx, int Ny) {
    int *A_storage= (int*)malloc(Nx * Ny*sizeof(int));
    int **A = (int**)malloc(Nx * sizeof(int*));

    for (int i=0; i<Nx; i++) {
        A[i] = &(A_storage[i*Ny]);
    }
    return A;
}

int **example_array() {
    int **A = allocate_2D_int(4, 5);
    A[0][0] = 1;
    A[0][1] = 5;
    A[0][2] = 6;
    A[0][3] = 3;
    A[0][4] = 1;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 4;
    A[1][3] = 1;
    A[1][4] = 7;
    A[2][0] = 7;
    A[2][1] = 2;
    A[2][2] = 3;
    A[2][3] = 1;
    A[2][4] = 2;
    A[3][0] = 3;
    A[3][1] = 2;
    A[3][2] = 2;
    A[3][3] = 5;
    A[3][4] = 3;
    return A;
}