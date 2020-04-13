#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>

#include "read_webgraph.c"
#include "countmutuallinks_omp.c"
#include "top_n_webpages_omp.c"

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
    int nr_threads = atoi(argv[2]);

    omp_set_num_threads(nr_threads);


    printf("Reading web graph as 2D table\n");
    read_graph_from_file1(filename, &N, &test_table);
    printf("Reading web graph as CRS format\n");
    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

    
    int *num_involvements1 = calloc(N, sizeof(int));
    int *num_involvements2 = calloc(N, sizeof(int));
    // Prints for a 2D table showing we links
    
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            printf("%i ", test_table[i][j]);
        }
        printf("\n");
    }
    

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
    

    printf("Counting mutual links from 2D table\n");
    int mutual_links1 = count_mutual_links1_omp(N, test_table, num_involvements1);
    printf("nr of mutual links: %i \n", mutual_links1);
    printf("Counting mutual links from CRS format\n");
    int mutual_links2 = count_mutual_links2_omp(N, N_links, row_ptr, col_idx, num_involvements2);
    printf("nr of mutual links: %i \n", mutual_links2);

    // Print showing num involvements
    
    printf("num_involvements: ");
    for (int j=0; j<N; j++) {
        printf("%d ", num_involvements1[j]);
    }
    printf("\n");
    

    printf("Top webpages\n");
    top_n_webpages_omp(N, num_involvements1, N, nr_threads);
    free(row_ptr);
    free(col_idx);
    free(num_involvements1);
    free(num_involvements2);
    return 0;
}