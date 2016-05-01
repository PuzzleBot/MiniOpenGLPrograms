#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <GL/glut.h>
 */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define WHITESPACE " \n\t\r"

#define START_WIDTH 1024
#define START_HEIGHT 768

#define VECX_NULL -99999999.1
#define VECY_NULL -99999999.1
#define VECZ_NULL -99999999.1

#define AMBIENT_K 0.4
#define DIFFUSE_K 0.4
#define SPECULAR_K 0.4
#define ATTENUATION 1.0
#define SPECULAR_FINE 32

#define AMBIENT_RED 0.4
#define AMBIENT_GREEN 0.4
#define AMBIENT_BLUE 0.4

/*Downscale the viewing plane so that it isn't as large as the resolution*/
#define PIXELS_PER_UNIT 1

typedef struct{
    long double x;
    long double y;
    long double z;
} Dim3Vector;

typedef struct{
    Dim3Vector pos;
    
    long double attenuation;
    
    long double r;
    long double g;
    long double b;
} LightData;


typedef struct{
    Dim3Vector pos;
    long double radius;
    
    long double r;
    long double g;
    long double b;
} SphereData;


void parseFile(FILE * fp);
void drawPixels();
void setPixelColour(int rowNum, int colNum, GLfloat red, GLfloat green, GLfloat blue);

void calculatePixels();
void printVector(Dim3Vector vector);
void normalize(Dim3Vector * vector);
long double findLength(Dim3Vector origin, Dim3Vector destination);
long double dotProduct(Dim3Vector vec1, Dim3Vector vec2);
int isOppositeFromPoint(Dim3Vector center, Dim3Vector point1, Dim3Vector point2);
int findDiscriminantSign(long double a, long double b, long double c);
Dim3Vector determineIntersection(Dim3Vector origin, Dim3Vector direction, int sphereIndex);
Dim3Vector determineSelfIntersection(Dim3Vector origin, Dim3Vector direction, int sphereIndex);
int determineFirstIntersection(Dim3Vector origin, Dim3Vector direction);
int isLightBlocked(Dim3Vector origin, Dim3Vector direction, int sphereSource);
