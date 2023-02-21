// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "rotate.h"

// This function returns the number of times the matrix should be rotated
int check_angle(char *angle)
{
	if (strcmp(angle, " 360") == 0 || strcmp(angle, " -360") == 0 ||
		strcmp(angle, " 0") == 0)
		return 0;
	if (strcmp(angle, " 90") == 0 || strcmp(angle, " -270") == 0)
		return 1;
	if (strcmp(angle, " 180") == 0 || strcmp(angle, " -180") == 0)
		return 2;
	if (strcmp(angle, " -90") == 0 || strcmp(angle, " 270") == 0)
		return 3;
	return -1;
}

// This function allocates an auxiliary matrix and rotates it
pixel **copy_rotate(image *img)
{
	pixel **new_matrix = (pixel **)malloc(img->width * sizeof(pixel *));
	if (!new_matrix)
		return NULL;

	for (int i = 0; i < img->width; i++) {
		new_matrix[i] = (pixel *)malloc(img->height * sizeof(pixel));

		if (!new_matrix[i]) {
			for (int j = 0; j < i; j++)
				free(new_matrix[i]);
			free(new_matrix);
			return NULL;
		}

		for (int j = 0; j < img->height; j++) {
			new_matrix[i][j].element = (double *)malloc(img->fields *
									   sizeof(double));

			if (!new_matrix[i][j].element) {
				free(new_matrix[i][j].element);
				return NULL;
			}

			// Transposing the matrix
			for (int k = 0; k < img->fields; k++)
				new_matrix[i][j].element[k] = img->matrix[j][i].element[k];
		}

		// Swap the pixels
		int x = img->height - 1;
		for (int j = 0; j < x; j++) {
			swap_adr(&new_matrix[i][j].element, &new_matrix[i][x].element);
			x--;
		}
	}
	return new_matrix;
}

// This function rotates the entire image 90 degrees clockwise
void rotate_all_90(image *img)
{
	pixel **new_matrix = copy_rotate(img);
	free_matrix(img->matrix, *img);
	swap(&img->width, &img->height);
	select_all(img);

	img->matrix = new_matrix;
}

// This function rotates the selection of an image 90 degrees clockwise
void rotate_selected_90(image *img)
{
	int i, j, k;
	for (i = img->y1; i < img->y2; i++) {
		for (j = img->x1 + i - img->y1; j < img->x2; j++) {
			swap_adr(&img->matrix[i][j].element,
					 &img->matrix[j + img->y1 - img->x1][i + img->x1 -
					 img->y1].element);
		}
	}
	for (k = img->y1; k < img->y2; k++) {
		i = img->x1;
		j = img->x2 - 1;
		while (i < j) {
			swap_adr(&img->matrix[k][i].element, &img->matrix[k][j].element);
			i++;
			j--;
		}
	}
}

// This function rotates 'angle' degrees a selection of the image
void rotate(image *img, int loaded)
{
	char angle[CMAX];
	fgets(angle, CMAX, stdin);
	angle[strlen(angle) - 1] = '\0';
	int a = check_angle(angle);

	if (!loaded) {
		printf("No image loaded\n");
		return;
	}

	if (a == -1) {
		printf("Unsupported rotation angle\n");
		return;
	}

	if (a == 0) {
		printf("Rotated%s\n", angle);
		return;
	}

	if (img->x2 - img->x1 == img->y2 - img->y1) {
		while (a) {
			rotate_selected_90(img);
			a--;
		}
		printf("Rotated%s\n", angle);
	} else if (img->x1 == 0 && img->y1 == 0 && img->x2 == img->width &&
			   img->y2 == img->height) {
		while (a) {
			rotate_all_90(img);
			a--;
		}
		printf("Rotated%s\n", angle);
	} else {
		printf("The selection must be square\n");
	}
}
