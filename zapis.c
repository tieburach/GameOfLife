#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>

#include "zapis.h"

void save_to_txt(generation_t *net, char *file_name) {
	int i, j;
	FILE *out = fopen(file_name, "w+");
	if (out == NULL) {
		fprintf(stderr, "Nie powiodl sie zapis ostatniej generacji do pliku TXT\n");
		return;	
		}
	fprintf(out, "%d %d\n", net->rows, net->cols);
	for (i = 0; i < net->rows; i++) {
		for (j = 0; j < net->cols; j++) {
			if ((condition(cell(net,i,j))) == ALIVE)
				fprintf(out, "%d %d\n", i + 1, j + 1);
		}
	}
}

void save_to_png(generation_t *net, char *file_name) {
	int x, y, i, j;
	int width, height;
	FILE *fp = NULL;
	png_byte color_type;
	png_byte bit_depth;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_pointers;
	width = 8 * net->cols;
	height = 8 * net->rows;
	bit_depth = 8;
	color_type = PNG_COLOR_TYPE_GRAY;
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	for (y=0; y<height; y++)
		row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

	for (y = 0; y < height; y+=8) {
		for (x = 0; x < width; x+=8) {
			if(condition(cell(net, y/8, x/8)) == ALIVE) { 
				for (i = 0; i < 8; i++) {
					for (j = 0; j < 8; j++)
						row_pointers[y + j][x + i] = 255;
				}
			} else {
				for (i = 0; i < 8; i++) {
					for (j = 0; j < 8; j++)
						row_pointers[y + j][x + i] = 0;
				}
			}
		}
	}
	/* zapis struktury do pliku */
	fp = fopen(file_name, "wb");
	if (!fp)
		printf("[write_png_file] Plik %s nie moze byc otwarty do zapisu\n", file_name);

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

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

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

	fclose(fp);
}
