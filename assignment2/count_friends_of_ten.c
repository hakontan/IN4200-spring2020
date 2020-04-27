#include <stdio.h>


int count_friends_of_ten(int M, int N ,int **v) {
    int sum = 0;
    int nr_friends = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // Checking horizontal axis
            if (i < M - 3) {
                for (int k = 0; k < 3; k++) {
                    sum += v[i+k][j];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
            //Checking vertical axis
            if (j < N - 3) {
                for (int k = 0; k < 3; k++) {
                    sum += v[i][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
            //Checking diagonal axis from left to right
            if (i < M - 3 && j < N - 3) {
                for (int k = 0; k < 3; k++) {
                    sum += v[i + k][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
            //checking diagonal axis from right to left
            if (i > M - 3 && j > N - 3) {
                for (int k = 0; k > -3; k--) {
                    sum += v[i + k][j + k];
                }
                if (sum == 10) {
                    nr_friends += 1;
                }
                sum = 0;
            }
        }
    }
    return nr_friends;
}