#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>


#include "read_webgraph.c"
#include "countmutuallinks.c"
#include "top_n_webpages_omp.c"

int main(int argc, char *argv[]) {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    int num_webpages;
    int n;
    char* filename = argv[1];
    int *row_ptr;
    int *col_idx;



    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);


    int *num_involvements = calloc(N, sizeof(int));

    int mutual_links2 = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);

    double time;
    int n_threads;
    double total_time;
    for (int i = 2; i <=8; i++) {
        // taking average over multiple timings to cancel out background
        // processes interfering.
        total_time = 0;
        for (int j = 0; j<100; j++) {
            omp_set_num_threads(i);
            time = omp_get_wtime();
            top_n_webpages_omp(N, num_involvements, 10, i);
            time = omp_get_wtime() - time;
            total_time += time;
        } 
        total_time /= 100;  
        printf("Time taken to rank top %i using web pages using %i threads: %g ms\n", 10, i, 1000 * total_time);
    }
}