#include "game.h"
#include "util.h"

int LoD (int n, int sum){
    if(n == 0 && sum == 3) {
        n = 1;
    } else if (n == 1 && (sum < 3 || sum > 4)) {
        n = 0;
    }
    return n;
}

int** play(int** matrix, int columns, int rows){
    int** next = allocate_matrix(columns, rows);

    for (int i = 1; i < columns-1; i++) {
        for (int j = 1; j < rows-1; j++) {
            int sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    sum += matrix[i + k - 1][j + l - 1];
                }
            }
            next[i][j] = LoD(matrix[i][j], sum);
        }
    }

    for (int i = 0; i < columns; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return next;
}