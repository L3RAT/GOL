#include "pnggen.h"

void make_png_file(char* file_name, int** data, int columns, int rows, int mag) {

    int width = columns * mag;
    int height = rows * mag;
    int** mag_data = allocate_matrix(width, height);

    for (int i = 0; i < (width); i++) {
        for (int j = 0; j < (height); j++) {
            mag_data[i][j] = data[i/mag][j/mag];
        }
    }

    int x, y;

    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_byte bit_depth = 8;

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

    for (y=0; y<height; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

    for (y=0; y<height; y++) {
        png_byte* row = row_pointers[y];
        for (x=0; x<width; x++) {
            if(mag_data[x][y] == 1) row[x] = 255;
            else row[x] = 0;
        }
    }

    FILE *fp = fopen(file_name, "wb");
    if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", file_name);

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    for (y=0; y<height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    for (int i = 0; i < width; i++) {
        free(mag_data[i]);
    }
    free(mag_data);


    fclose(fp);
}