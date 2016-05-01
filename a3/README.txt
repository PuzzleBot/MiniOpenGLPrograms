*************************
Brandon Tan
ID: 0845538
CIS*4800
Assignment 3
*************************

** Compilation **
- Type "make" to compile.
- Type "./a3" to run.


** Assumptions **
- The program assumes that the file is of the specified format.
    - Most importantly, the first part of the file describing the width and
      height must be accurate.
- Each line in the file may not be longer than 2047 characters long.
- The machine running the program is assumed to have enough memory to
  run it (having not enough memory causes an exit() during parsing).
- The only input files are the seven given, located under the images/ directory.


** All specified features have been implemented:
- A light constantly rotates around a cube on a plane, in a circle pattern
  (a glowing sphere is drawn at the light's position)
- The cube has a texture that can be swapped using Key '1'
- The cube has a fake shadow drawn with it that is positioned on the plane



** File organization **
	a3.c: The example A2 file, with heavy modifications for this assignment
	a3.h: Includes, macros and prototypes
	draw.c: Code for drawing vertices, shadows, and placing the light
	imageData.c: Code for handling file data
	test.c: A test driver for testing the memory handling (ignore this file)

	/images/: Contains the seven texture files given, plus one unused test file
	          created by me

	