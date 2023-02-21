// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)
#include "basics.h"

// This function frees a given matrix
void free_matrix(pixel **matrix, image img)
{
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++)
			free(matrix[i][j].element);
		free(matrix[i]);
	}
	free(matrix);
}

// This function exits the program by freeing the loaded matrix
void exit_program(image img, int loaded)
{
	if (loaded == 1)
		free_matrix(img.matrix, img);
	else
		printf("No image loaded\n");
}

// This function swaps the values of two integers
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

// This function swaps two pointers
void swap_adr(double **a, double **b)
{
	double *aux = *a;
	*a = *b;
	*b = aux;
}

// This function makes sure that the value of x stays in the given range
double clamp(double x, double min, double max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return x;
}
