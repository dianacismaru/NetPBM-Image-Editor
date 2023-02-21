// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef IMAGE_H
#define IMAGE_H

// Maximum number of characters in a command
#define CMAX 30

// Maximum number of characters in a file type
#define TMAX 3

// Maximum number of characters in a file name
#define FMAX 50

// Unsigned char is too long!
typedef unsigned char uc;

// This structure stores each pixel of an image
typedef struct {
	double *element;
} pixel;

// This structure stores the data of an image
typedef struct {
	int width, height, max_value;
	int format, fields;
	char color_type[TMAX];
	pixel **matrix;
	int x1, y1, x2, y2;
} image;

#endif
