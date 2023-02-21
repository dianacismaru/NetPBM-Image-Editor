// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef APPLY_H
#define APPLY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "basics.h"

// This function applies the gaussian blur filter
extern void gaussian_blur(image * img, pixel * **matrix);

// This function applies the blur filter
extern void blur(image *img, pixel ***matrix);

// This function applies the sharpen filter
extern void sharpen(image *img, pixel ***matrix);

// This function applies the edge filter
extern void edge(image *img, pixel ***matrix);

// This function applies any filter to the image
extern void apply_filter(image *img, pixel ***m, double ker[3][3]);

// Base function for apply command
extern void apply(image *img, int loaded);

#endif
