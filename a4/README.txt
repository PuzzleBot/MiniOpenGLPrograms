*************************
Brandon Tan
ID: 0845538
CIS*4800
Assignment 4
*************************


** Compilation **
- Type "make" to compile.
- Type "./a4 <filename>" to run with the specified file.


** Input File format **

light    x  y  z    r  g  b
sphere   x  y  z  R  r  g  b
    ...
 
 
where x,y,z are the centre of the sphere or the location of the light,
r,g,b is the colour, R is the radius of the sphere.

Example files can be found under ./inputs/


** Assumptions **
- The program assumes that the file is of the specified format.
- Each line in the file may not be longer than 2047 characters long.
- The machine running the program is assumed to have enough memory to
  run it (having not enough memory causes an exit() during parsing).
- The file is assumed to end in a newline character '\n'
- Sphere sizes are small enough that performing power operations on them
  will not overflow the program. (numbers within -2500 < x < 2500 are safe)
- No parameters or line intersections touch the exact point
  [-99999999.1, -99999999.1, -99999999.1]

** Other important notes **
- The viewing plane is literally 1024x768 units big. Sphere sizes and positions
  should be in the hundreds to account for this.
- Specular and diffuse lighting is bugged for objects to the bottom-left
  in relation to the light source (on the xy plane): The lighting is on
  the opposite side of where it is supposed to be, and does not cast a shadow.
  (The bug has something to do with rays going in the wrong direction for very
   specific rays, but I can't seem to find out what specific rays this applies
   to)
- I have provided input files to demonstrate the functioning parts of the program
  (and that one big bug) all under /inputs/:
	test1: Grey spheres and a white light in a straight line
	test2: Multicoloured spheres and a white light, in 3 different dimensions
	test3: Same as test 2, but with a red light
	cornerX: (Don't use these) Used by me to try to resolve the bug. All
	         of them have a single grey sphere with a light in one corner.


** All specified features have been implemented:
- File reading
- Ray tracing using ambient, diffuse and specular lighting
- Shadows




** File organization **
	a4.c: Parts of the A2 file for initializing OpenGL
	a4.h: Includes, macros and prototypes
	imageData.c: Code for reading file data into memory
	ray.c: Vector math functions, illumination calculations, and pixel drawing
	test.c: A test driver for testing the memory handling (ignore this file)

	/inputs/: Test inputs for testing the application. (Descriptions above)

	