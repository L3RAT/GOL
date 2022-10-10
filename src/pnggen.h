#pragma once

#include <stdlib.h>
#include <png.h>

#include "util.h"

void make_png_file(char* file_name, int** data, int columns, int rows, int mag);