/* Derived from scene.c in the The OpenGL Programming Guide */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
/* Linux Headers */
/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

/* OSX Headers */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

typedef struct{
    int shape;
    int colour;
    int iterations;
    
    double size;
    
    double inx;
    double xoff;
    double iny;
    double yoff;
    double inz;
    double zoff;
    
    double inxr;
    double xroff;
    double inyr;
    double yroff;
    double inzr;
    double zroff;
    
    double inxs;
    double xsoff;
    double inys;
    double ysoff;
    double inzs;
    double zsoff;
    
} ObjectData;

void parseStream(FILE * inputFile);
void printObject(ObjectData object);
