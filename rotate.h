// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef ROTATE_H
#define ROTATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "image.h"
#include "basics.h"
#include "select.h"

// This function returns the number of times the matrix should be rotated
extern int check_angle(char *angle);

// This function allocates an auxiliary matrix and rotates it
extern pixel **copy_rotate(image *img);

// This function rotates the entire image 90 degrees clockwise
extern void rotate_all_90(image *img);

// This function rotates the selection of an image 90 degrees clockwise
extern void rotate_selected_90(image *img);

// This function rotates 'angle' degrees a selection of the image
extern void rotate(image *img, int loaded);

#endif
