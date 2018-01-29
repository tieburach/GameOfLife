#ifndef ZAPIS_H
#define ZAPIS_H

#include <stdio.h>
#include "generacja.h"
#include "komorka.h"

void save_to_txt(generation_t *net, char *txt_pattern);

void save_to_png(generation_t *net, char *png_pattern);

#endif
