#include <stdio.h>
#include <stdlib.h>


int count_mutual_links1 (int N, char **table2D, int *num_involvements) {
    int mutual_links_tot = 0;
    num_involvements = calloc(N, sizeof(int));
    int c = 0;
    int num_involvements_per_row = 0;
    int current;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (table2D[i][j] == 1) {
                for (int k = j + 1; k < N; k++) {
                    current = table2D[i][k];
                    mutual_links_tot += current;
                    if (c == 0) {
                        num_involvements_per_row += current;
                    }
                }
            num_involvements[j] += num_involvements_per_row;
            c = 1;
            }
        }
        c = 0;
        num_involvements_per_row = 0;
    }

    printf("num_involvements: ");
    for (int j=0; j<N; j++) {
        printf("%d ", num_involvements[j]);
    }
    printf("\n");

    return mutual_links_tot;
}

int count_mutual_links2 (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements) {
    num_involvements = calloc(N, sizeof(int));
    int mutual_links_tot = 0;
    int n_pages;
    int count = 0;


    for (int i = 0; i < N; i++) {
        n_pages = row_ptr[i + 1] - row_ptr[i];
        printf("%i\n", n_pages);
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++){
            num_involvements[col_idx[j]] += n_pages - 1;
        }
        if (n_pages > 1) {
            while (n_pages > 1) {
                count += n_pages - 1;
                n_pages--;
            }
            mutual_links_tot += count;
            count = 0;
        }
    }
    printf("num_involvements: ");
    for (int j=0; j<N; j++) {
        printf("%d ", num_involvements[j]);
    }
    printf("\n");
    return mutual_links_tot;
}

