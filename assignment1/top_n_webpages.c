
void top_n_webpages(int num_webpages, int *num_involvements, int n) {
    int *top_n = calloc(n, sizeof(int));
    int *web_page_nr = calloc(n, sizeof(int));

    printf("num webpages: %i\n", num_webpages);
    printf("top n: %i\n", n);

    
    for (int i = 0; i < num_webpages ; i++) {
        printf("%i ", num_involvements[i]);
    }

    printf("\n");
    for (int i = 0; i < num_webpages; i++) {
        for (int j = 0; j < n; j++) {
            if (num_involvements[i] >= top_n[j]) {
                //Shuffling every value in top_n and web_page_nr
                //one index backward to make room for new larger value.
                for (int k = n - 1 ; k > j ; k--) {   
                    top_n[k] = top_n[k-1];
                    web_page_nr[k] = web_page_nr[k-1];
                }

                //Updating with new largest value.
                top_n[j] = num_involvements[i];
                web_page_nr[j] = i;
                break;
            }   
        }
    }
    for (int i = 0; i < n ; i++) {
        printf("Web page nr %i had %i involvements\n ", web_page_nr[i] + 1, top_n[i]);
    }
    free(top_n);
    free(web_page_nr);
}

