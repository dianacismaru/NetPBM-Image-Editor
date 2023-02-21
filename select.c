// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "select.h"

// Function that checks if a string represents a positive number
int is_valid_number(char *word)
{
	int n = strlen(word);
	for (int i = 0; i < n; i++) {
		if (isdigit(word[i]) == 0) {
			// Negative number
			if (word[i] == '-')
				return 0;
			// Not a number
			return -1;
		}
	}
	// Positive number
	return 1;
}

// This function checks the argument for SELECT command
int check_arg_select(char *s)
{
	char *word = strtok(s, "\n ");
	int all = 0, ct = 0, junk = 0, negative = 0;

	while (word) {
		if (!strcmp(word, "ALL")) {
			// Counting how many times does the "ALL" word appears
			all++;
		} else if (is_valid_number(word) == 1) {
			// Counting how many valid numbers appear
			ct++;
		} else if (is_valid_number(word) == -1) {
			// Counting how many incorrect words appear
			junk++;
		} else if (is_valid_number(word) == 0) {
			// Counting how many negative numbers appear
			negative++;
		}
		word = strtok(NULL, "\n ");
	}

	if (all == 1 && !ct && !junk && !negative) {
		// Select ALL case
		return 0;
	} else if (!all && ct == 4 && !junk && !negative) {
		// Valid coordinates case
		return 1;
	}
	// Invalid command case
	if (junk || (negative + ct) < 4)
		return -2;

	// Invalid set of coordinates case
	return -1;
}

// This function gets the valid coordinates from a string
void get_coordinates(char *s, int *cx1, int *cy1, int *cx2, int *cy2)
{
	int array[4], i = 0;
	char *p = strtok(s, " ");
	while (p) {
		array[i++] = atoi(p);
		p = strtok(NULL, " ");
	}
	*cx1 = array[0];
	*cy1 = array[1];
	*cx2 = array[2];
	*cy2 = array[3];

	// Place in correct order
	if (*cx1 > *cx2)
		swap(cx1, cx2);
	if (*cy1 > *cy2)
		swap(cy1, cy2);
}

// This function selects the coordinates of the entire new image
void select_all(image *img)
{
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = img->width;
	img->y2 = img->height;
}

// This function gets a selection of the image
void select(image *img, int loaded)
{
	// Creating a copy for the arguments, since the initial string will be
	// destroyed by strtok
	char arguments[CMAX], copy[CMAX];
	fgets(arguments, CMAX, stdin);
	strcpy(copy, arguments);

	// Checking if there is any image loaded
	if (loaded == 0) {
		printf("No image loaded\n");
		return;
	}

	// Using a variable that indicates the type of selection
	int ok = check_arg_select(arguments);

	if (ok == -1) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (ok == -2) {
		printf("Invalid command\n");
		return;
	}

	if (ok == 0) {
		select_all(img);
		printf("Selected ALL\n");
		return;
	}

	// Creating auxiliary coordinates that store valid numbers
	int cx1, cy1, cx2, cy2;
	get_coordinates(copy, &cx1, &cy1, &cx2, &cy2);

	if (cx2 == cx1 || cy2 == cy1 || cx2 > img->width || cy2 > img->height) {
		printf("Invalid set of coordinates\n");
		return;
	}

	// Update the coordinates
	img->x1 = cx1;
	img->x2 = cx2;
	img->y1 = cy1;
	img->y2 = cy2;
	printf("Selected %d %d %d %d\n", img->x1, img->y1, img->x2, img->y2);
}
