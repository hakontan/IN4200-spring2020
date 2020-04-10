#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

#include "read_webgraph.c"
#include "countmutuallinks_omp.c"

int main() {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    int num_webpages;
    int n;
    char **test_table;
    int *row_ptr;
    int *col_idx;

    read_graph_from_file1("hundred_nodes.txt", &N, &test_table);

    read_graph_from_file2("hundred_nodes.txt", &N, &N_links, &row_ptr, &col_idx);


    int *num_involvements1 = calloc(N, sizeof(int));
    int *num_involvements2 = calloc(N, sizeof(int));

    double start = omp_get_wtime();
    int mutual_links1 = count_mutual_links1_omp(N, test_table, num_involvements1);
    double time = omp_get_wtime() - time;
    printf("Time taken to count mutual links using 2D tableunparallelized: %f ms\n", time);

    start = omp_get_wtime();
    int mutual_links2 = count_mutual_links2_omp(N, N_links, row_ptr, col_idx, num_involvements2);
    time = omp_get_wtime() - time;
    printf("Time taken to count mutual links using CRS format unparallelized: %f ms\n", time);
}