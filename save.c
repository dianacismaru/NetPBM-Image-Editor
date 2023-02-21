// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "save.h"

// This function is used for printing a matrix
void print_matrix(image img, int format, FILE *fp)
{
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			for (int k = 0; k < img.fields; k++) {
				if (format == 0) {
					int aux = clamp(round(img.matrix[i][j].element[k]), 0,
							  img.max_value);
					fprintf(fp, "%d ", aux);
				} else {
					uc aux = clamp(round(img.matrix[i][j].element[k]), 0,
							 img.max_value);
					fwrite(&aux, sizeof(uc), 1, fp);
				}
			}
		}
		if (format == 0)
			fprintf(fp, "\n");
	}
}

// This function saves an image
void save(image *img, int loaded)
{
	char filename[FMAX];
	scanf("%s", filename);

	// Creating a string that stores either the argument, if any, or enter
	char arg[CMAX];
	fgets(arg, CMAX, stdin);

	// Checking if there is any image loaded
	if (!loaded) {
		printf("No image loaded\n");
		return;
	}

	FILE *fp = fopen(filename, "wb");
	if (!fp) {
		printf("Cannot open %s\n", filename);
		return;
	}

	int format;
	// Printing the magic-word, depending on the argument
	if (strcmp(arg, "\n") == 0 || (arg[0] == ' ' && arg[1] == '\n')) {
		// Binary file
		format = 1;
		if (img->fields == 1)
			fprintf(fp, "P5\n");
		else
			fprintf(fp, "P6\n");

	} else {
		// Plain file
		format = 0;
		if (img->fields == 1)
			fprintf(fp, "P2\n");
		else
			fprintf(fp, "P3\n");
	}

	// Printing the image info
	fprintf(fp, "%d %d\n%d\n", img->width, img->height, img->max_value);

	// Printing the pixels
	print_matrix(*img, format, fp);

	printf("Saved %s\n", filename);
	fclose(fp);
}
