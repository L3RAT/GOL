#include "util.h"

int** allocate_matrix (int columns, int rows) {
    int** data = malloc(sizeof(int*)*columns);
    for (int i = 0; i < columns; i++) {
        data[i] = calloc(rows, sizeof(int));
    }
    if (data == NULL) {
        fprintf(stderr, "Nie udało się zaalokować pamięci na macierz!\n");
        exit(99);
    }
    return data;
}

int** init (int *c, int *r, FILE *input) {

    if (fscanf(input, "%i ", c) != 1 || *c < 3) {
        fprintf(stderr, "Macierz musi mieć conajmniej 3 kolumny!\n");
        exit(2);
    } else if (fscanf(input, "%i", r) != 1 || *r < 3) {
        fprintf(stderr, "Macierz musi mieć conajmniej 3 rzędy!\n");
        exit(2);
    }

    int** data = allocate_matrix(*c, *r);

    for (int i = 0; i < *r; i++) {
        for (int j = 0; j < *c; j++) {
            if (fscanf(input, "%i", &(data[j][i])) != 1 || (data[j][i]) < 0 || (data[j][i]) > 1) {
                printf("Macierz nie odpowiada podanym parametrom lub zawiera niedozwolony symbol!\n");
                exit(3);
            }
        }
    }

    return data;
}

int** init_rand (int *c, int *r) {

    srand(time(NULL));
    *c = ((rand() % (MAX_RES-2))+3);
    *r = *c;

    int** data = allocate_matrix(*c, *r);

    for (int i = 1; i < *r-1; i++) {
        for (int j = 1; j < *c-1; j++) {

            if ( (rand() % (RAND_RATIO+1)) == 0) {
                data[j][i] = 1;
            } else {
                data[j][i] = 0;
            }

//            data[j][i] = ((rand() % 2) * (rand() % 2) * (rand() % 2) ) % 2;
        }
    }

    return data;
}