#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define WHITESPACE " \n\t\r"
#define DEBUG printf("DEBUG\n")

#define LENGTH 9
#define DISPLAYHEIGHT 15
#define LIGHT_RADIUS 20

#define NUMBER_OF_TEXTURES 7

#define PLANE_MULTIPLIER 1

#define GREY {0.5, 0.5, 0.5, 1.0}

GLubyte *** colourMap = NULL;

void drawScene();
void parseStream(FILE * fp);
void printColourMap();

int width = 0;
int height = 0;
int depth = 0;


int main(){
    FILE * fp = fopen("images/test.ppm", "r");
    parseStream(fp);
    printColourMap();
    
    return(0);
}
