#include <stdio.h>
#include <stdlib.h>


int count_mutual_links1 (int N, char **table2D, int *num_involvements) {
    int mutual_links_tot = 0;
    int col_dim_ind = 0;
    int mutual_links_perpage = 0;
    num_involvements = malloc(N*sizeof(int));
    
    for (int j=0; j<N; j++){
        for (int i=0; i<N; i++) {
            if (table2D[i][j] == 1) {
                for (int k=0; k<N; k++){
                    if(k != j){
                        num_involvements[j] += table2D[k][i];
                    }
                }
            }
        }
    }

    for (int i = 0; i<N; i++) {
        mutual_links_tot += num_involvements[i];
    }
    return mutual_links_tot / 2.0;
}

//int count_mutual_links1 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements) {
    
 