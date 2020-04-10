#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>

#include "read_webgraph.c"
#include "countmutuallinks.c"
#include "top_n_webpages.c"

int main() {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    int num_webpages;
    int n;
    char **test_table;
    int *row_ptr;
    int *col_idx;
    double start;

    //read_graph_from_file1("hundred_nodes.txt", &N, &test_table);
    read_graph_from_file2("hundred_nodes.txt", &N, &N_links, &row_ptr, &col_idx);

    
    int *num_involvements1 = calloc(N, sizeof(int));
    int *num_involvements2 = calloc(N, sizeof(int));
    // Prints for a 2D table showing we links
    /*
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            printf("%i ", test_table[i][j]);
        }
        printf("\n");
    }
    */

    // Prints for col_idx and row_ptr
    
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
    

    //printf("counting mutual links using table\n");
    start = omp_get_wtime();
    int mutual_links1 = count_mutual_links1(N, test_table, num_involvements1);
    printf("Time elapsed counting mutual links from Table: %f seconds", (omp_get_wtime() - start));

    //printf("# Mutual links 1 = %i\n", mutual_links1);

    printf("counting mutual links using CRS format\n");
    int mutual_links2 = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements2);
    printf("# Mutual links 2 = %i\n", mutual_links2);

    // Print showing num involvements
    /*
    printf("num_involvements: ");
    for (int j=0; j<N; j++) {
        printf("%d ", num_involvements[j]);
    }
    printf("\n");
    */

    printf("Top webpages parallelized\n");
    top_n_webpages(N, num_involvements, 10);
    printf("Top webpages parallelized\n");
    pragma_top_n_webpages(N, num_involvements, 10);
    free(row_ptr);
    free(col_idx);
    return 0;
}