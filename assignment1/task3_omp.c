#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>


#include "read_webgraph.c"
#include "countmutuallinks.c"
#include "top_n_webpages_omp.c"

int main() {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    int num_webpages;
    int n;

    int *row_ptr;
    int *col_idx;



    read_graph_from_file2("hundred_nodes.txt", &N, &N_links, &row_ptr, &col_idx);


    int *num_involvements = calloc(N, sizeof(int));

    int mutual_links2 = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
    
    clock_t time = clock();
    top_n_webpages_omp(N, num_involvements, 10);
    time = clock() - time;
    printf("Time taken to rank top %i web pages: %f ms\n",(10, (double) 1000 * time / CLOCKS_PER_SEC));

}