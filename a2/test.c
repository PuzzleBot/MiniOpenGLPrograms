/*THIS IS NOT ACTUALLY PART OF THE FUNCTIONALITY OF THE ASSIGNMENT
  I just wrote this as a way of testing my data structures for memeory leaks*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
#define WHITE {0.0, 0.0, 0.0, 1.0}
#define GREEN {0.2, 1.0, 0.2, 1.0}
#define BROWN {0.5, 0.25, 0.05, 1.0}

#define GREY {0.5, 0.5, 0.5, 1.0}

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

void transformCamera(double degrees, double zoomDist);


double ** heightMap = NULL;
double *** diffuseColourMap = NULL;
Dim3Vector *** vertexNormals = NULL;
Dim3Vector *** triangleNormals = NULL;

int width = 0;
int height = 0;
int depth = 0;

double cameraZoom = 0.0;

int main(int argc, char ** argv){
    FILE *fp;
    
    if ((fp = fopen(argv[1], "r")) == 0) {
        printf("Error, failed to find the file specified.\n");
        exit(0);
    }
    
    parseStream(fp);
    printVertexNormals();
    freeMapData();
    
    return(0);
}