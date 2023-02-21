Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

# NetPBM Image Editor

## Description of the project
This project implementation is able to work with **NetPBM images** by processing
**text** and **binary** files. I implemented some commands that allow you to 
**apply filters** on these images.

The main header that I've been using (`image.h`) includes important
data about an image:

- width and height;
- type;
- maximum value a pixel can have;
- a **matrix** in which its elements are represented by vectors of pixels;
- format (0 - plain or 1 - binary);
- **number of fields** (1 field for grayscale or 3 fields for color);
- **coordinates** for a selection;

A few remarks that I have before diving into the actual program:
* `basics.c` include auxiliary functions, sunt as swapping, clamping or freeing the memory of a matrix;
* in the `*.h` files, I've placed some not-so-pretty asterisks just 
because the coding style checker told me to do so;
* I've placed a lot of comments through the entire program, so
please, take them into consideration as well.

## Commands
My code is split in a lot of commands and I am about to describe them
separatedly:

1. LOAD:
   ~~~~
	Load a matrix by allocating memory for it and reading its data and pixels from a binary or plain file;

2. SELECT:
   ~~~~~~
	Get a selection of the loaded image by using the given coordinates. Valid coordinates are those that meet the following conditions:
	- do not exceed the width or height of the image;
	- the difference between the 'x' points or the 'y' points is positive;
	- do not include negative numbers;
	- do not include alphabet letters or symbols;

3. CROP:
   ~~~~
	Crop the previous selection of the image by allocating a new matrix with new values and by freeing the old one.


4. ROTATE:
   ~~~~~~
	Rotate the entire image or a square selection of it.
	The action is possible by rotating the image repeatedly by 90 degrees clockwise, until the needed angle is reached. The only valid angles are: 0, +-90, +-180, +-270, +-360 degrees.

5. APPLY:
   ~~~~~
	Apply diverse filters on the loaded image, such as Blur, Gaussian Blur, Sharpen or Edge.
	The transformation is possible by using image kernels: for each 3x3 block of pixels, each pixel is multiplied by the corresponding entry of the kernel, and then, the sum of those represents the new pixel. However, the edge of the image is not affected by the kernel.

6. SAVE:
   ~~~~
	Save the data and the pixels of an image to a specified path by printing them to the corresponding file. In this function, the image can be saved either plain or binary.

7. EXIT:
   ~~~~
	Free all the previously allocated memory and close the running program.

8. other(?):
   ~~~~~~~~
	In this case, any other commands that are written in the terminal will be considered invalid.
