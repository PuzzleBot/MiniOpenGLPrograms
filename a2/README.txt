*************************
Brandon Tan
ID: 0845538
CIS*4800
Assignment 2
*************************


** Assumptions **
- The program assumes that the file is of the specified format.
    - Most importantly, the first part of the file describing the width and
      height must be accurate.
- Each line in the file may not be longer than 2047 characters long.
- The machine running the program is assumed to have enough memory to
  run it (having not enough memory causes an exit() during parsing).


** Other Important Notes **
- Given textures are automatically scaled down so that the max height is 10.
  (The user can still rescale it using the right mouse with no restraint)
- Zooming is limited so that the user cannot zoom in infinitely, to attempt
  to prevent them from zooming through the object. (can zoom out infinitely)
- The point light source is positioned at 0, 15, 0.


** All specified interface features have been implemented:
- Left mouse down + vertical movement: zoom
- Left mouse down + horizontal movement: rotate around center of object
- Right mouse down + vertical movement: rescale y values of object

- Key 1: Flat shading
- Key 2: Smooth shading
- Key 3: Grey colour scheme
- Key 4: Height-based colour scheme
- Key 5: Randomized colour change per vertex


** File organization **
    a2.c : Given A2 code excluding headers, heavily modified for this assignment.
    a2.h : Headers, prototypes and data structure definitions.
    camera.c : Code for changing the view angle and zoom, triggered by the mouse.
    imageData.c : Functions which handle parsing and manipulating data.
    draw.c : Functions which use the data given to generate the image.
    test.c : A testing file used by me to access memory leaks. (Not used directly
             in the assignment, ignore it)
    textures/ : Texture files given.

** File format **
Input files follow the standard format for PGM files. That is, they are of the
format:

P2
<width> <height> <depth>
<number1> <number2> ...

where width and height define the rectangular size of the image, depth is the
maximum value for any of the following values in the file, and the numbers
define the "highness" of the image at each unit point on the image.
