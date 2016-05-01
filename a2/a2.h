#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
/*
 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <GL/glut.h>
 */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define WHITESPACE " \n\t\r"
#define DEBUG printf("DEBUG\n")

/*At the start, scale the heightmap down so that the max height is 10*/
#define DISPLAYHEIGHT 10

/*Mouse actions*/
#define NO_MOUSE_DOWN 0
#define LEFT_MOUSE_DOWN 1
#define RIGHT_MOUSE_DOWN 2

/*Colour options*/
#define GREY_SCHEME 0
#define HEIGHT_SCHEME 1
#define RANDOM_SCHEME 2

/*Colours for the height colour scheme*/
#define WHITE {0.9, 0.9, 0.9, 1.0}
#define GREEN {0.3, 0.8, 0.3, 1.0}
#define BROWN {0.6, 0.35, 0.1, 1.0}

#define GREY {0.5, 0.5, 0.5, 1.0}

/*My custom vector data type*/
typedef struct{
    double xLen;
    double yLen;
    double zLen;
} Dim3Vector;

void parseStream(FILE * fp);
void drawMap();
void display(void);
void freeMapData();
Dim3Vector * createVector(double xLen, double yLen, double zLen);
Dim3Vector * crossProduct(Dim3Vector * vector1, Dim3Vector * vector2);
Dim3Vector * toUnitVector(Dim3Vector * vector);
Dim3Vector * averageVectors(Dim3Vector ** vectorList, int numberOfVectors);
void calculateNormals();
void printVertexNormals();
void toColourScheme(int scheme);

void transformCamera(double degrees, double zoomDist);
