// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef BASICS_H
#define BASICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image.h"

// This function frees a given matrix
extern void free_matrix(pixel * *matrix, image img);

// This function exits the program by freeing the loaded matrix
extern void exit_program(image img, int loaded);

// This function swaps the values of two integers
extern void swap(int *a, int *b);

// This function swaps two pointers
extern void swap_adr(double **a, double **b);

// This function makes sure that the value of x stays in the given range
extern double clamp(double x, double min, double max);

#endif
