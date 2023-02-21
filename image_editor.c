// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "apply.h"
#include "basics.h"
#include "crop.h"
#include "image.h"
#include "load.h"
#include "rotate.h"
#include "save.h"
#include "select.h"

int main(void)
{
	char command[CMAX];
	image img;
	img.matrix = NULL;
	int loaded = 0;

	while (1) {
		scanf("%s", command);

		// Checking if we have a valid command or not
		if (!strcmp(command, "EXIT")) {
			exit_program(img, loaded);
			return 0;

		} else if (!strcmp(command, "LOAD")) {
			// Free the previous image if there is any
			if (img.matrix)
				free_matrix(img.matrix, img);

			load(&img, &loaded);

		} else if (!strcmp(command, "SELECT")) {
			select(&img, loaded);

		} else if (!strcmp(command, "ROTATE")) {
			rotate(&img, loaded);

		} else if (!strcmp(command, "CROP")) {
			if (!loaded) {
				printf("No image loaded\n");
			} else {
				img.matrix = crop(&img, img.matrix);
				printf("Image cropped\n");
			}

		} else if (!strcmp(command, "SAVE")) {
			save(&img, loaded);

		} else if (!strcmp(command, "APPLY")) {
			apply(&img, loaded);

		} else {
			// Read the remaining arguments
			fgets(command, CMAX, stdin);
			printf("Invalid command\n");
		}
	}
	return 0;
}
