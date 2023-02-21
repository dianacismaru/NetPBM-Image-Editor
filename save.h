// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "image.h"
#include "basics.h"

// This function is used for printing a matrix
extern void print_matrix(image img, int format, FILE * fp);

// This function saves an image
extern void save(image *img, int loaded);

#endif
