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
    read_graph_from_file1("webgraph_test.txt", &N, &test_table);
    read_graph_from_file2("webgraph_test.txt", &N, &N_links, &row_ptr, &col_idx);

    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            printf("%i ", test_table[j][i]);
        }
        printf("\n");
    }

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

    
    int mutual_links1 = count_mutual_links1(N, test_table, num_involvements);
    printf("# Mutual links 1 = %i\n", mutual_links1);

    int mutual_links2 = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
    printf("# Mutual links 2 = %i\n", mutual_links2);
    
    free(row_ptr);
    free(col_idx);
    return 0;
}