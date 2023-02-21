// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef SELECT_H
#define SELECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image.h"
#include "basics.h"

// This function checks if a string represents a positive number
extern int is_valid_number(char *word);

// This function checks the argument for SELECT command
extern int check_arg_select(char *s);

// This function gets the valid coordinates from a string
extern void get_coordinates(char *s, int *cx1, int *cy1, int *cx2, int *cy2);

// This function selects the coordinates of the entire new image
extern void select_all(image *img);

// This function gets a selection of the image
extern void select(image *img, int loaded);

#endif
