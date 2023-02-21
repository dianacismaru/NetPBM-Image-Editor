// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "load.h"

// This function skips eventual comments that are found in the file
void skip_comments(FILE *fp)
{
	char c = '\n';
	do {
		while (c != '\n')
			fscanf(fp, "%c", &c);
		fscanf(fp, "%c", &c);
	} while (c == '#');

	// Going back one position
	fseek(fp, -1, SEEK_CUR);
}

// This function checks the magic-word in order to find out the number
// of fields needed for each pixel
int nr_fields(char *color_type)
{
	if (strcmp(color_type, "P2") == 0 || strcmp(color_type, "P5") == 0)
		return 1;

	if (strcmp(color_type, "P3") == 0 || strcmp(color_type, "P6") == 0)
		return 3;

	return -1;
}

// This function checks the magic-word in order to find out if the pixels'
// values are stored plan or binary
int file_type(char *color_type)
{
	// Plain type
	if (strcmp(color_type, "P2") == 0 || strcmp(color_type, "P3") == 0)
		return 0;

	// Binary type
	if (strcmp(color_type, "P5") == 0 || strcmp(color_type, "P6") == 0)
		return 1;

	return -1;
}

// This function is meant to read a matrix and allocate memory for it
pixel **read_matrix(image img, FILE *fp)
{
	pixel **matrix;
	uc v[3];

	matrix = malloc(img.height * sizeof(pixel *));
	if (!matrix)
		return NULL;
	for (int i = 0; i < img.height; i++) {
		matrix[i] = malloc(img.width * sizeof(pixel *));

		if (!matrix[i]) {
			for (int j = 0; j < i; j++)
				free(matrix[j]);
			free(matrix);
			return NULL;
		}

		for (int j = 0; j < img.width; j++) {
			matrix[i][j].element = malloc(img.fields * sizeof(double));
			if (!img.format) {
				for (int k = 0; k < img.fields; k++)
					fscanf(fp, "%hhu", &v[k]);
			} else {
				fread(v, sizeof(uc), img.fields, fp);
			}

			for (int k = 0; k < img.fields; k++)
				matrix[i][j].element[k] = (double)v[k];
		}
	}
	return matrix;
}

// This function loads an image into the memory
void load(image *img, int *loaded)
{
	char filename[FMAX];
	scanf("%s", filename);

	img->matrix = NULL;
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		printf("Failed to load %s\n", filename);
		*loaded = 0;
		return;
	}

	// Reading the image data and skipping eventual comments
	skip_comments(fp);
	fscanf(fp, "%s", img->color_type);
	skip_comments(fp);
	fscanf(fp, "%d%d", &img->width, &img->height);
	skip_comments(fp);
	fscanf(fp, "%d", &img->max_value);
	skip_comments(fp);

	img->format = file_type(img->color_type);
	img->fields = nr_fields(img->color_type);

	// Skipping over an endline if the file is binary
	if (img->format == 1)
		fseek(fp, 1, SEEK_CUR);

	img->matrix = read_matrix(*img, fp);
	printf("Loaded %s\n", filename);
	*loaded = 1;

	select_all(img);
	fclose(fp);
}
