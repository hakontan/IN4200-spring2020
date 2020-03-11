#include <stdio.h>
#include <stdlib.h>
#include "read_webgraph.c"
#include "countmutuallinks.c"
#include <time.h>

int main() {
    // Testing of algorithms while developing
    
    int N;
    int N_links;
    char **test_table;
    int *row_ptr;
    int *col_idx;
    int *num_involvements;
    //read_graph_from_file1("web-NotreDame.txt", &N, &test_table);
    clock_t start = clock();
    read_graph_from_file2("web-NotreDame.txt", &N, &N_links, &row_ptr, &col_idx);
    clock_t stop = clock();

    //int diff = (stop - start) * 1000 / CLOCKS_PER_SEC;
    //printf("%i\n", diff);
    //printf("%i\n", N);
    //int mutual_links1 = count_mutual_links1(N, test_table, num_involvements);
    //printf("%i", mutual_links1);
    
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
    
   return 0;
}