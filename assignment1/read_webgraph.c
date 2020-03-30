

char** allocate_2D_char(int Nx, int Ny) {
    /*
    Allocates memory and initializes a 2D  array 
    of dimensions Nx x Ny with zeros.

    Arguments
    ----------
    int Nx:
        Number of data points in x-direction
    int Ny:
        Number of data points in y-direction
    Returns:
        Zero matrix A
    */
    char** A;
    A = malloc(Ny * sizeof(double *));
    A[0] = calloc(Nx * Ny, sizeof(double));

    for (int i = 1; i < Ny; i ++) {
        A[i] = &A[0][Ny * i];
    }
    for (int i=0; i<Nx; i++) {
        for (int j=0; j<Ny; j++) {
            A[i][j] = 0;
        }
    }   
    return A;
}

void read_graph_from_file1 (char *filename, int *N, char ***table2D) {

    int edges;
    int from;
    int to;

    FILE *infile;
    infile = fopen(filename, "r");
    fscanf(infile, "%*[^\n]\n"); // skip one line
    fscanf(infile, "%*[^\n]\n"); // skip one line
    fscanf(infile, "%*s %*s %d %*s %d \n", N, &edges);

    // Initialize table2D as zeros.
    *table2D = allocate_2D_char(*N, *N);

    
    fscanf(infile, "%*[^\n]\n"); // skip one line


    while (fscanf(infile, "%d %d\n", &from, &to) != EOF) {
        if(to != from) {
            (*table2D)[to][from] = 1;
        }
    }
}

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx) {

    int from;
    int to;
    int c;
    int col_idx_index;

    FILE *infile;
    infile = fopen(filename, "r");
    fscanf(infile, "%*[^\n]\n"); // skip one line
    fscanf(infile, "%*[^\n]\n"); // skip one line

    fscanf(infile, "%*s %*s %d %*s %d \n", N, N_links);
    int *to_arr = malloc(*N_links * sizeof(int));
    int *from_arr = malloc(*N_links * sizeof(int));
    *col_idx = malloc(*N_links * sizeof(int));
    *row_ptr = malloc((*N + 1) * sizeof(int));
    (*row_ptr)[0] = 0; // First row starts on index zero

    fscanf(infile, "%*[^\n]\n"); // skip one line
    c = 0;
    while (fscanf(infile, "%d %d\n", &from, &to) != EOF) {
        if(from != to) {
              (*row_ptr)[to + 1]++;
              to_arr[c]     = to;
              from_arr[c]   = from;
              c++;
        }
    }

    col_idx_index = 0;
    for (int i=0; i<*N; i++) {
        for (int j=0; j< *N_links; j++){
            if (to_arr[j] == i) {
                (*col_idx)[col_idx_index] = from_arr[j];
                col_idx_index++;
            }
        }
    }

    for (int i = 1; i < (*N+1); i++) {     
        (*row_ptr)[i] += (*row_ptr)[i-1];
    }
    free(to_arr);
    free(from_arr);
}

