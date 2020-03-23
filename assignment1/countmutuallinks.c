#include <stdio.h>
#include <stdlib.h>


int count_mutual_links1 (int N, char **table2D, int *num_involvements) {
    int mutual_links_tot = 0;
    num_involvements = calloc(N, sizeof(int));

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (table2D[j][i] == 1) {
                for (int k = j + 1; k < N; k++) {
                    num_involvements[i] += table2D[k][i];
                }
            }
        }
    }

    for (int i = 0; i<N; i++) {
        mutual_links_tot += num_involvements[i];
    }
    return mutual_links_tot;
}

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements) {
    num_involvements = calloc(N, sizeof(int));
    int mutual_links_tot = 0;
    int n_pages;
    int count = 0;
    printf("row_ptr: ");
    for (int j=0; j<N+1; j++) {
        printf("%d ", row_ptr[j]);
    }
    printf("\n");

    for (int i = 1; i < N +1; i++) {
        n_pages = row_ptr[i] - row_ptr[i-1];
        printf("%i\n", n_pages);

        if (n_pages > 1) {
            num_involvements[col_idx[i-1]] += 1;
            while (n_pages > 1) {
                count += n_pages - 1;
                n_pages--;
            }
            mutual_links_tot += count;
            count = 0;
        }
    }
    return mutual_links_tot;
}

