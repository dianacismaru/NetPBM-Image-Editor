// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef LOAD_H
#define LOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image.h"
#include "basics.h"
#include "select.h"

// This function skips eventual comments that are found in the file
extern void skip_comments(FILE * fp);

// This function checks the magic-word in order to find out the number
// of fields needed for each pixel
extern int nr_fields(char *color_type);

// This function checks the magic-word in order to find out if the pixels'
// values are stored plan or binary
extern int file_type(char *color_type);

// This function is meant to read a matrix and allocate memory for it
extern pixel **read_matrix(image img, FILE *fp);

// This function loads an image into the memory
extern void load(image *img, int *loaded);

#endif
