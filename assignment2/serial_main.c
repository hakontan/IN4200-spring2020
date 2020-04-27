#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "count_friends_of_ten.c"

int main() {
    int N = 5;
    int M = 5;
    int friends_of_ten;
    srand (time(NULL));

    int** v;
    v = malloc(N * sizeof(double *));
    v[0] = malloc(N * M * sizeof(double));

    for (int i = 1; i < M; i ++) {
        v[i] = &v[0][M * i];
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            v[i][j] = rand() % (9 + 1 - 0) + 0;
        }
    }

    friends_of_ten = count_friends_of_ten(M, N, v);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%i ", v[i][j]);
        }
        printf("\n");
    }

    printf("Friends of ten: %i\n", friends_of_ten);
}