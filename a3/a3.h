#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
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

#define LENGTH 10
#define DISPLAYHEIGHT 15
#define LIGHT_RADIUS 20

#define NUMBER_OF_TEXTURES 7

#define PLANE_MULTIPLIER 1
#define NUMBER_OF_DIVISIONS 100

#define GREY {0.5, 0.5, 0.5, 1.0}

void drawScene();
void parseStream(FILE * fp);
void loadTexture(char * fileName, int textureID);
void printColourMap();
void drawFakeShadow(GLfloat lightPosX, GLfloat lightPosY, GLfloat lightPosZ);