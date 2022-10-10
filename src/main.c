#include "pnggen.h"
#include "game.h"
#include "util.h"

int main(int argc, char** argv)
{
    int columns, rows;
    int *c = &columns;
    int *r = &rows;
    int generations = MAX_FRAMES;
    int delay = DELAY;

    printf("Dzień dobry!\nJestem programem symulującym grę w życie Conwaya.\n");

    if(argc == 1) {
        printf("Aby rozpocząć symulację podaj plik wejściowy z macierzą binarną lub podaj argument 'rand',\n");
        printf("aby program sam wygenerował taką macierz.\n\n");
        printf("Dodatkowo jako drugi parametr możesz sprecyzować liczbę pokoleń, która będzie zasymulowana,\n");
        printf("a jako trzeci parametr - liczbę milisekund jaką ma trwać jedna klatka wygenerowanego pliku GIF\n");
        exit(1);
    }

    FILE *input = argc > 1 ? fopen(argv[1], "r") : stdin;

    int** data;

    if(strcmp("rand", argv[1]) != 0) {
        if (input == NULL) {
            fprintf(stderr, "Plik wejściowy %s nie istnieje!\n", argv[1]);
            exit(1);
        }
        data = init(c,r,input);
    } else {
        data = init_rand(c,r);
    }
    if (argc > 2) {
        if (isdigit(*argv[2])) {
            generations = atoi(argv[2]);
        } else {
            printf("Uwaga! Drugi argument musi być liczbą!\n");
            exit(1);
        }
    }

    if (argc > 3) {
        if (isdigit(*argv[3])) {
            delay = atoi(argv[3]);
        } else {
            printf("Uwaga! Trzeci argument musi być liczbą!\n");
            exit(1);
        }
    }

    system("rm *.png *.gif");

    char buf[BUF_MAX];
    int mag = columns > rows ? MAX_RES/columns : MAX_RES/rows;

    for (int i = 0; i < generations; i++) {
        snprintf(buf, sizeof(buf), "img%03d.png", i);
        make_png_file(buf, data, columns, rows, mag);
        data = play(data, columns, rows);
    }

    char temp[BUF_MAX];
    snprintf(temp,  sizeof(temp), "convert -delay %d -loop 0 *.png loop.gif", delay);
    system(temp);

    for (int i = 0; i < columns; i++) {
        free(data[i]);
    }
    free(data);
    printf("\nPodróż w czasie %d pokoleń do przodu zakończona sukcesem!\n",generations);

    return 0;
}