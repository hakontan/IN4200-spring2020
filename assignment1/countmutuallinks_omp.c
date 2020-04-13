#include <omp.h>
#include <stdbool.h>

int count_mutual_links1_omp (int N, char **table2D, int *num_involvements) {
    int mutual_links_tot = 0;
    bool first_val = true;
    int num_involvements_per_row = 0;
    int current;

    #pragma omp parallel for private(current, first_val, num_involvements_per_row) reduction(+: mutual_links_tot, num_involvements[:N])
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (table2D[i][j] == 1) {
                for (int k = j + 1; k < N; k++) {
                    current = table2D[i][k];
                    mutual_links_tot += current;

                    // Only counting number of involvements per row for the first value on each row
                    // as all other webpages on the row contains the same number of involvements.
                    if (first_val == true) {
                        num_involvements_per_row += current;
                    }
                }
            num_involvements[j] += num_involvements_per_row;
            first_val = false;
            }
        }
        first_val = true;
        num_involvements_per_row = 0;
    }
    
    return mutual_links_tot;
}




int count_mutual_links2_omp (int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements) {
    int mutual_links_tot = 0;
    int n_pages;
    int count = 0;

    #pragma omp parallel for private(n_pages, count) reduction(+: mutual_links_tot, num_involvements[:N])
    for (int i = 0; i < N; i++) {
        n_pages = row_ptr[i + 1] - row_ptr[i];
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++){
            num_involvements[col_idx[j]] += n_pages - 1;
        }
        if (n_pages > 1) {
            // Doing a cumulative sum within each of the rows defined by row_ptr
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

