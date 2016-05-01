#include "a4.h"

LightData lightSource;
SphereData * spheres;
int numberOfSpheres = 0;

GLfloat * pixelData;
int width = START_WIDTH;
int height = START_HEIGHT;

/*Viewpoint coordinates*/
double viewpointX = 0.0;
double viewpointY = 0.0;
double viewpointZ = 0.0;

int main(int argc, char ** argv){
    FILE *fp;
    int  i, j;
    int  red, green, blue;
    
    if ((fp = fopen(argv[1], "r")) == 0) {
        printf("Error, failed to find the file named %s.\n", argv[1]);
        exit(0);
    }
    
    parseFile(fp);
    
    fclose(fp);
    
    drawPixels();
}

