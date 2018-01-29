#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#define _POSIX_SOURCE
#include <sys/stat.h>
#include <unistd.h>
#undef _POSIX_SOURCE

#include "generacja.h"
#include "komorka.h"
#include "zapis.h"
#include "sasiedztwo.h"

const char *usage = "Usage: \n"
		    "./Life -n N -l sciezka [-s nazwa] [-w nazwa2] [-f F] [-m] \n"
		    "\tN - liczba generacji\n"
		    "\tsciezka - sciezka dostepu do generacji poczatkowej\n"
		    "\t[opcjonalnie] nazwa - poczatek nazwy plikow png\n"
		    "\t[opcjonalnie] nazwa2 - nazwa pliku z osatnia generacja txt\n"
		    "\t[opcjoonalnie] F - liczba generacji ktora bedzie zapisana do png, domyslnie N generacji \n"
		    "\t[opcjonalnie]  jezeli podany argument -m to sasiedztwo zmienia sie na von Neumanna, domyslnie Moorea";			
	
int main(int argc, char **argv) {
	int a, opt, n, f = 0;
	char *gen_zero;
	char *png_pattern = "generacja";
	char png_title[100];
	char number[10];
	const char *format = ".png";
	char *txt_pattern= "ostatni.txt";
	const char *new_dir = "pliki_utworzone";
	FILE *in = NULL;
	int last_to_txt =1;
	int (*neighbourhood)(generation_t *, int, int) = Moore_ngbh;
	
	generation_t *current, *new, *tmp;
	if (argc < 5) {
		puts(usage);
		return EXIT_FAILURE;
	}
	while ((opt = getopt(argc, argv, "n:l:s:f:m")) != -1) {
		switch (opt) {
			case 'n': 
				n = atoi(optarg);
				f = n;
				break;
			case 'l':
				gen_zero = optarg;
				break;
			case 's':
				png_pattern = optarg;
				break;
			case 'f':
				f = atoi(optarg);
				break;
			case 'm':
				neighbourhood = Neumann_ngbh;
				break;	
			default:
				fprintf(stderr, "%s: Nie prawidłowy argument wywołania %c\n", argv[0], opt);
				puts(usage);
				exit(EXIT_FAILURE);
		}
	}
	if (gen_zero == NULL || ((in = fopen(gen_zero, "r")) == NULL)) {
		fprintf(stderr, "%s: program nie moze odczytac pliku pierwszej generacji\n", argv[0]);
		return EXIT_FAILURE;
	}
	current = load_from_file(in);
	new = init_gen(current->rows, current->cols);
	if (mkdir(new_dir, S_IRWXU|S_IRGRP|S_IXGRP) != 0) {
		if (errno == EEXIST) {
			if (chdir(new_dir) != 0) {
				perror("error");
			}
		} else {
			perror("error");
		}
	} else if (chdir(new_dir) != 0) {
		perror("error");
	}
	strcpy(png_title, png_pattern);
	strcat(png_title, "0.png");
	save_to_png(current, png_title); 
	for (a = 1; a <= n; a++) {
		strcpy(png_title, png_pattern);
		if (neighbourhood == Moore_ngbh){
		next_generation(current, new, neighbourhood);
		}
		else if(neighbourhood == Neumann_ngbh){
		next_generation2(current, new, neighbourhood);
		}
		if (a <= f) {
			sprintf(number, "%d", a);
			strcat(png_title, number);
			strcat(png_title, format);
			save_to_png(new, png_title); 
		}
		if (a == n && last_to_txt == 1){
			save_to_txt(new, txt_pattern);
			}
		tmp = current;
		current = new;
		new = tmp;
	}
	free_gen(current);
	free_gen(new);
	if (chdir("..") != 0) 
		perror("error");
	exit(EXIT_SUCCESS);	
}
