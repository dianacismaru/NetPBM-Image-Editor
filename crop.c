// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "crop.h"

// This function allocates a matrix with the new dimensions
pixel **load_selected_matrix(int height, int width, image img, pixel **matrix)
{
	pixel **cropped_matrix = (pixel **)malloc(height * sizeof(pixel *));

	if (!cropped_matrix)
		return NULL;
	for (int i = 0; i < height; i++) {
		cropped_matrix[i] = (pixel *)malloc(width * sizeof(pixel));

		if (!cropped_matrix[i]) {
			for (int j = 0; j < i; j++)
				free(cropped_matrix[i]);
			free(cropped_matrix);
			return NULL;
		}

		for (int j = 0; j < width; j++) {
			cropped_matrix[i][j].element = (double *)malloc(img.fields *
											sizeof(double));

			if (!cropped_matrix[i][j].element) {
				free(cropped_matrix[i][j].element);
				return NULL;
			}

			for (int k = 0; k < img.fields; k++)
				cropped_matrix[i][j].element[k] = matrix[img.y1 + i][img.x1
												  + j].element[k];
		}
	}
	return cropped_matrix;
}

// This function crops an image into a given selection
pixel **crop(image *img, pixel **matrix)
{
	// Setting the new dimensions
	int new_height = img->y2 - img->y1;
	int new_width = img->x2 - img->x1;

	// Creating a new matrix with the new dimensions
	pixel **cropped_matrix = load_selected_matrix(new_height, new_width, *img,
												  matrix);

	// Free the initial matrix
	free_matrix(matrix, *img);

	// Selecting the entire cropped image
	img->height = new_height;
	img->width = new_width;
	select_all(img);

	return cropped_matrix;
}
