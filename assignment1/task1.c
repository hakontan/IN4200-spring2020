#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "read_webgraph.c"

int main(int argc, char *argv[]) {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    int num_webpages;
    int n;
    char **test_table;
    int *row_ptr;
    int *col_idx;
    double start;
    char *filename = argv[1];


    clock_t time = clock();
    read_graph_from_file1(filename, &N, &test_table);
    time = clock() - time;
    printf("Time taken to read web graph and store as 2D table: %f ms\n", (double) 1000 * time / CLOCKS_PER_SEC);

    time = clock();
    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);
    time = clock() - time;
    printf("Time taken to read web graph and store col_idx and row_ptr: %f ms\n", (double) 1000 * time / CLOCKS_PER_SEC);

    // Prints for the 2D table
    /*
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            printf("%i ", test_table[i][j]);
        }
        printf("\n");
    }
    */


    // Prints for col_idx and row_ptr
    /*
    printf("col_idx: ");
    for (int j=0; j<N_links; j++) {
        printf("%d ", col_idx[j]);
    }
    printf(" \n");
    
    printf("row_ptr: ");
    for (int j=0; j<N+1; j++) {
        printf("%d ", row_ptr[j]);
    }
    printf("\n");
    */
}