
void top_n_webpages_omp(int num_webpages, int *num_involvements, int n, int nr_threads) {

    int pages_per_thread = num_webpages / nr_threads;
    //int top_pages_per_thread = n / nr_threads;

    int *top_n = calloc(n*nr_threads, sizeof(int));
    int *web_page_nr = calloc(n*nr_threads, sizeof(int));

    int *top_n_short  = calloc(n, sizeof(int));
    int *web_page_nr_short = calloc(n, sizeof(int));
    //printf("num webpages: %i\n", num_webpages);
    //printf("top n: %i\n", n);


    
    #pragma omp parallel
    {
    int thread_num = omp_get_thread_num();
    //printf("I am thread nr %i \n", thread_num);
    // One thread has to do some extra work if number of webpages cannot be evenly split.
    if (thread_num == nr_threads - 1) {
        for (int i = pages_per_thread * thread_num; i < num_webpages; i++) {
            for (int j = thread_num * n ; j < n * nr_threads; j++) {
                if (num_involvements[i] >= top_n[j]) {
                    // Shuffling every value in top_n and web_page_nr
                    // one index backward to make room for new larger value.
                    for (int k = n * nr_threads - 1 ; k > j; k--) {   
                        top_n[k] = top_n[k-1];
                        web_page_nr[k] = web_page_nr[k-1];
                    }
                    // Updating with new largest value.
                    top_n[j] = num_involvements[i];
                    web_page_nr[j] = i;
                    break;
                }   
            }
        }
    }
    
    if (thread_num < nr_threads -1) {
        for (int i = thread_num * pages_per_thread; i < (thread_num + 1) * pages_per_thread; i++) {
            //printf("I am thread nr %i on iteration %i\n", thread_num, i);
            for (int j = thread_num * n; j < (thread_num + 1) * n; j++) {
                //printf("I am thread nr %i on iteration %i\n", thread_num, j);
                if (num_involvements[i] >= top_n[j]) {
                    // Shuffling every value in top_n and web_page_nr
                    // one index backward to make room for new larger value.
                    for (int k =  (thread_num + 1) * n - 1 ; k > j ; k--) {   
                        top_n[k] = top_n[k-1];
                        web_page_nr[k] = web_page_nr[k-1];
                    }
                    // Updating with new largest value.
                    top_n[j] = num_involvements[i];
                    web_page_nr[j] = i;
                    break;
                }
            }
        }
    }
    }

    for (int i = 0; i < n*nr_threads; i++) {
        for (int j = 0; j < n; j++) {
            if (top_n[i] >= top_n_short[j]) {
                //Shuffling every value in top_n and web_page_nr
                //one index backward to make room for new larger value.
                for (int k = n - 1 ; k > j ; k--) {   
                    top_n_short[k] = top_n_short[k-1];
                    web_page_nr_short[k] = web_page_nr_short[k-1];
                }
                //Updating with new largest value.
                top_n_short[j] = top_n[i];
                web_page_nr_short[j] = web_page_nr[i];
                break;
            }   
        }
    }

    
    for (int i = 0; i < n ; i++) {
        printf("Web page nr %i had %i involvements\n ", web_page_nr_short[i] + 1, top_n_short[i]);
    }
    
    free(top_n);
    free(web_page_nr);
    free(top_n_short);
    free(web_page_nr_short);
}