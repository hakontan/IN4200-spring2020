int** allocate_2D_int(int Nx, int Ny) {
    int *A_storage= (int*)malloc(Nx * Ny*sizeof(int));
    int **A = (int**)malloc(Nx * sizeof(int*));

    for (int i=0; i<Nx; i++) {
        A[i] = &(A_storage[i*Ny]);
    }
    return A;
}