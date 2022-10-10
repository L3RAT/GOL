#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_RES 640
#define MAX_FRAMES 20
#define DELAY 20
#define BUF_MAX 64
#define RAND_RATIO 4

int** allocate_matrix (int columns, int rows);
int** init (int *c, int *r, FILE *input);
int** init_rand(int *c, int *r);