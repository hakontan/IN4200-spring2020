#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

#include "read_webgraph.c"
#include "countmutuallinks_omp.c"

int main(int argc, char *argv[]) {
    
    int N;
    int N_links;
    int num_webpages;
    int n;
    char **test_table;
    int *row_ptr;
    int *col_idx;

    char *filename = argv[1];

    read_graph_from_file1(filename, &N, &test_table);

    read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);



    double time;
    double total_time_1;
    double total_time_2;

    for (int i=2; i <= 8; i++) {
        total_time_1 = 0;
        total_time_2 = 0;
        int *num_involvements1 = calloc(N, sizeof(int));
        int *num_involvements2 = calloc(N, sizeof(int));

        // taking average over multiple timings to cancel out background
        // processes interfering.
        for (int j=0; j<100; j++) {
            omp_set_num_threads(i);

            time = omp_get_wtime();
            int mutual_links1 = count_mutual_links1_omp(N, test_table, num_involvements1);
            time = omp_get_wtime() - time;
            total_time_1 += time;

            time = omp_get_wtime();
            int mutual_links2 = count_mutual_links2_omp(N, N_links, row_ptr, col_idx, num_involvements2);
            time = omp_get_wtime() - time;
            total_time_2 += time;
        }
        total_time_1 /= 100;
        total_time_2 /= 100;
        printf("Time taken to count mutual links using 2D table parallelized using %i threads: %g ms\n", i, (double) 1000 * total_time_1);
        printf("Time taken to count mutual links using CRS format parallelized using %i threads: %g ms\n", i, (double) 1000 * total_time_2);
        free(num_involvements1);
        free(num_involvements2);
    }
}