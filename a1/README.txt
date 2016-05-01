*************************
Brandon Tan
ID: 0845538
CIS*4800
Assignment 1
*************************

** Compilation **
- Type "make" to compile.
- Type "./a1 <filename>" to run with the specified file.


** Assumptions **
- The program assumes that the file is of the specified format.
- The file must end with a newline '\n' character.
- There may be no more than 10 object descriptions. (10 lines not including the first)


All specified features have been implemented:
- Basic object transformations
- Recursive display


File organization:
    a1.c : Given A1 code excluding headers, plus added transformation code.
    a1.h : Headers, prototypes and data structure definitions.
    shapeData.c : Code regarding parsing and storing file data.


** Input File Details **

The first line of the file is a list of headings for each column in
the file. Every input file will have this line.

After there first line there will be at most 10 more lines in the file.
Each of these lines describes an object in the scene.


File Columns
============

shape
-----
0	sphere
1	cube
2	torus
3	cone


colour
------
0	blue
1	red
2	green
3	white


iterations -the total number of times the object will be drawn
           -for non-recursive examples this number will be set to 1
           -recursive files will have a number greater than 1 on at least one line

size -the number of units to pass to the OpenGL draw command for the size of the object


translation values
------------------
inx, iny, inz -the initial position for the object (for the first one drawn)
xoff, yoff, zoff -the amount to translate the object in each iteration (translation offset
		 applied to each object after the first)

rotation values
---------------
inxr, inyr, inzr -the initial rotations of the object (for the first one drawn)
xroff, yroff, zroff -the amount to rotate object in each iteration (rotation offset
		applied to each object after the first) 

scale values
------------
inxs, inys, inzs -the initial scale applied to the object (for the first one drawn), used
		with the glScalef() function
xsoff, ysoff, zsoff -the amount to scale the object in each iteration (scale offset
		applied to each object after the first -multiplied by previous scale vale)


