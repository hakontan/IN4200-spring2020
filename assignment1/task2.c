#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>

#include "read_webgraph.c"
#include "countmutuallinks.c"

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


    read_graph_from_file1("hundred_nodes.txt", &N, &test_table);

    read_graph_from_file2("hundred_nodes.txt", &N, &N_links, &row_ptr, &col_idx);


    int *num_involvements1 = calloc(N, sizeof(int));
    int *num_involvements2 = calloc(N, sizeof(int));

    clock_t time = clock();
    int mutual_links1 = count_mutual_links1(N, test_table, num_involvements1);
    time = clock() - time;
    printf("Time taken to count mutual links using 2D tableunparallelized: %f ms\n", (double) 1000 * time / CLOCKS_PER_SEC);

    time = clock();
    int mutual_links2 = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements2);
    time = clock() - time;
    printf("Time taken to count mutual links using CRS format unparallelized: %f ms\n", (double) 1000 * time / CLOCKS_PER_SEC);
}