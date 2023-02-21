// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "apply.h"

// This function applies the gaussian blur filter
void gaussian_blur(image *img, pixel ***matrix)
{
	double kernel[3][3] = {{0.0625, 0.125, 0.0625},
						   {0.125, 0.25, 0.125},
						   {0.0625, 0.125, 0.0625}};
	apply_filter(img, matrix, kernel);
}

// This function applies the blur filter
void blur(image *img, pixel ***matrix)
{
	double kernel[3][3] = {{0.1111, 0.1111, 0.1111},
						   {0.1111, 0.1111, 0.1111},
						   {0.1111, 0.1111, 0.1111}};
	apply_filter(img, matrix, kernel);
}

// This function applies the sharpen filter
void sharpen(image *img, pixel ***matrix)
{
	double kernel[3][3] = {{0.0, -1.0, 0.0},
						   {-1.0, 5.0, -1.0},
						   {0.0, -1.0, 0.0}};
	apply_filter(img, matrix, kernel);
}

// This function applies the edge filter
void edge(image *img, pixel ***matrix)
{
	double kernel[3][3] = {{-1.0, -1.0, -1.0},
						   {-1.0, 8.0, -1.0},
						   {-1.0, -1.0, -1.0}};
	apply_filter(img, matrix, kernel);
}

// This function applies any filter to the image
void apply_filter(image *img, pixel ***m, double ker[3][3])
{
	// Creating an auxiliary matrix
	pixel **copy = malloc(img->height * sizeof(pixel *));
	if (!copy)
		return;
	for (int i = 0; i < img->height; i++) {
		copy[i] = malloc(img->width * sizeof(pixel));
		if (!copy[i]) {
			for (int j = 0; j < i; j++)
				free(copy[i]);
			free(copy);
			return;
		}
		for (int j = 0; j < img->width; j++) {
			copy[i][j].element = malloc(3 * sizeof(double));
			if (!copy[i][j].element) {
				free(copy[i][j].element);
				return;
			}
		}
	}

	// Applying the calculation to the pixels that are not on the edge of the
	// image and store the results in the new matrix
	for (int i = img->y1; i < img->y2; i++) {
		for (int j = img->x1; j < img->x2; j++) {
			if (i && j && i != (img->height - 1) && j != (img->width - 1)) {
				for (int k = 0; k < 3; k++) {
					double x = (*m)[i - 1][j - 1].element[k] * ker[0][0] +
							(*m)[i - 1][j].element[k] * ker[0][1] +
							(*m)[i - 1][j + 1].element[k] * ker[0][2] +
							(*m)[i][j - 1].element[k] * ker[1][0] +
							(*m)[i][j].element[k] * ker[1][1] +
							(*m)[i][j + 1].element[k] * ker[1][2] +
							(*m)[i + 1][j - 1].element[k] * ker[2][0] +
							(*m)[i + 1][j].element[k] * ker[2][1] +
							(*m)[i + 1][j + 1].element[k] * ker[2][2];
					copy[i][j].element[k] = clamp(x, 0, img->max_value);
				}
			} else {
				for (int k = 0; k < 3; k++)
					copy[i][j].element[k] = (*m)[i][j].element[k];
			}
		}
	}

	// Copying the pixels of the new matrix to the intial matrix
	for (int i = img->y1; i < img->y2; i++)
		for (int j = img->x1; j < img->x2; j++)
			for (int k = 0; k < 3; k++)
				(*m)[i][j].element[k] = copy[i][j].element[k];

	free_matrix(copy, *img);
}

// Base function for apply command
void apply(image *img, int loaded)
{
	char parameter[CMAX];
	fgets(parameter, CMAX, stdin);

	// Checking if there is any image loaded
	if (!loaded) {
		printf("No image loaded\n");
		return;
	}

	// Checking if there is any parameter given
	if (!strcmp(parameter, "\n")) {
		printf("Invalid command\n");
		return;
	}

	// Checking if the image is grayscale
	if (img->fields == 1) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	parameter[strlen(parameter) - 1] = '\0';

	if (!strcmp(parameter, " EDGE")) {
		edge(img, &img->matrix);
	} else if (!strcmp(parameter, " SHARPEN")) {
		sharpen(img, &img->matrix);
	} else if (!strcmp(parameter, " BLUR")) {
		blur(img, &img->matrix);
	} else if (!strcmp(parameter, " GAUSSIAN_BLUR")) {
		gaussian_blur(img, &img->matrix);
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}
	printf("APPLY%s done\n", parameter);
}
