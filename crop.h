// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef CROP_H
#define CROP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image.h"
#include "basics.h"
#include "select.h"

// This function allocs a matrix with the new dimensions
extern pixel * *load_selected_matrix(int height, int width, image img,
									 pixel * *matrix);

// This function crops an image into a given selection
extern pixel **crop(image *img, pixel **matrix);

#endif
