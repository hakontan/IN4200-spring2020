#include <stdio.h>
#include <stdlib.h>

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
    
    //printf ("%d %d\n", *N, edges);
    
    fscanf(infile, "%*[^\n]\n"); // skip one line


    while (fscanf(infile, "%d %d\n", &from, &to) != EOF) {
        if(to != from) {
            (*table2D)[from][to] = 1;
        }
    }
}

void read_graph_from_file2 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx) {

    int from;
    int to;
    
    int c = 0;
    int from_tmp = 0;
    int to_tmp =0;

    int col_idx_value = 0;
    int col_idx_ind = 0;

    int row_ptr_ind = 1;
    int row_ptr_value = 0;

    FILE *infile;
    infile = fopen(filename, "r");
    fscanf(infile, "%*[^\n]\n"); // skip one line
    fscanf(infile, "%*[^\n]\n"); // skip one line

    fscanf(infile, "%*s %*s %d %*s %d \n", N, N_links);
    //printf("%d %d\n", *N, *N_links);
    *col_idx = malloc(*N_links*sizeof(int));
    *row_ptr = malloc((*N + 1)*sizeof(int));
    (*row_ptr)[0] = 0; // First row starts on index zero

    fscanf(infile, "%*[^\n]\n"); // skip one line

    
    while (fscanf(infile, "%d %d\n", &from, &to) != EOF) {
        if(to != from) {
            (*col_idx)[col_idx_ind] = to;
            col_idx_ind++;
            row_ptr_value++;
            c++;
            // test if we have changed row
            if (from_tmp < from) {
                int *tmp_array = malloc(c*sizeof(int));


                (*row_ptr)[row_ptr_ind] = row_ptr_value - 1;
                row_ptr_ind++; 
                from_tmp = from;

                //Sorting col_idx for the current row
                for (int i=(*row_ptr)[row_ptr_ind - 1]; i < (*row_ptr)[row_ptr_ind]; i++) {
                    tmp_array[i] = (*col_idx)[i];
                }
                //Bubble sort algorithm
                for (int i = 0; i < c; i++) {   
                    for (int j = 0; j < c - i - 1; j++) { 
                        if (tmp_array[j] > tmp_array[j + 1]) {  
                            int tmp = tmp_array[j];
                            tmp_array[j] = tmp_array[j + 1];
                            tmp_array[j + 1] = tmp;
                        }
                    }
                }

                for (int i=(*row_ptr)[row_ptr_ind]; i < (*row_ptr)[row_ptr_ind] + c; i++) {
                    (*col_idx)[i] = tmp_array[i];
                }
                c = 0;
                free(tmp_array);
            }    
        }
    }
    (*row_ptr)[row_ptr_ind] = col_idx_ind;
    /*
    // Sorting col_idx
    int c = 0;
    int j;
    int col_idx_j;
    int col_idx_jp1;
    for (int i = 0; i<*N_links; i++) {
        for (j = *row_ptr[i]; j<*row_ptr[i+1] - 1; j++) {
            if (*col_idx[j] > *col_idx[j+1]) {
                col_idx_j = *col_idx[j];
                col_idx_jp1 = *col_idx[j+1];

                *col_idx[j] = col_idx_jp1;
                *col_idx[j+1] = col_idx_j;
            }

        }
    }
    */
}

int main() {
    // Testing of algorithms while developing
    int N;
    int N_links;
    char **test_table;
    int *row_ptr;
    int *col_idx;
    read_graph_from_file2("webgraph_test.txt", &N, &N_links, &row_ptr, &col_idx);
    printf("col_idx: ");
    for (int j=0; j<N_links; j++) {
        printf("%d ", col_idx[j]);
    }
    printf(" \n");
    printf("row_ptr: ");
    for (int j=0; j<N+1; j++) {
        printf("%d ", row_ptr[j]);
    }
    free(row_ptr);
    free(col_idx);
    /*
    read_graph_from_file1("web-NotreDame-shorter.txt", &N, &test_table);
    printf("mf\n");
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            printf("%d %d %d\n", i, j, test_table[i][j]);
        }
    }
    free(test_table);
    */

   return 0;
}