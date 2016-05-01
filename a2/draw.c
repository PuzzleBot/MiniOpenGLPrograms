#include "a2.h"

extern double ** heightMap;
extern GLfloat *** diffuseColourMap;
extern Dim3Vector *** vertexNormals;
extern Dim3Vector *** triangleNormals;

extern int width;
extern int height;
extern int depth;

extern double cameraZoom;

/* flags used to control the appearance of the image */
extern int lineDrawing;	// draw polygons as solid or lines
extern int lighting;	// use diffuse and specular lighting
extern int smoothShading;  // smooth or flat shading

extern int colourMode;

void drawMap(){
    int i;
    int j;
    
    calculateNormals();
    
    glEnable(GL_NORMALIZE);
    
    if(smoothShading == 1){
        /*Smooth shaded triangles (vertex normals)*/
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                /*Draw counterclockwise triangles*/
                if((i < height - 1) && (j > 0)){
                    glBegin(GL_TRIANGLES);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j]);
                    glNormal3f(vertexNormals[i][j]->xLen,
                               vertexNormals[i][j]->yLen,
                               vertexNormals[i][j]->zLen);
                    glVertex3f(j, heightMap[i][j], i);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j-1]);
                    glNormal3f(vertexNormals[i][j-1]->xLen,
                               vertexNormals[i][j-1]->yLen,
                               vertexNormals[i][j-1]->zLen);
                    glVertex3f(j - 1, heightMap[i][j - 1], i);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i+1][j]);
                    glNormal3f(vertexNormals[i+1][j]->xLen,
                               vertexNormals[i+1][j]->yLen,
                               vertexNormals[i+1][j]->zLen);
                    glVertex3f(j, heightMap[i + 1][j], i + 1);
                    glEnd();
                }
                
                if((i > 0) && (j < width - 1)){
                    glBegin(GL_TRIANGLES);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j]);
                    glNormal3f(vertexNormals[i][j]->xLen,
                               vertexNormals[i][j]->yLen,
                               vertexNormals[i][j]->zLen);
                    glVertex3f(j, heightMap[i][j], i);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j+1]);
                    glNormal3f(vertexNormals[i][j+1]->xLen,
                               vertexNormals[i][j+1]->yLen,
                               vertexNormals[i][j+1]->zLen);
                    glVertex3f(j + 1, heightMap[i][j + 1], i);
                    
                    /*Get the colour, normal, and place the vertex*/
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i-1][j]);
                    glNormal3f(vertexNormals[i-1][j]->xLen,
                               vertexNormals[i-1][j]->yLen,
                               vertexNormals[i-1][j]->zLen);
                    glVertex3f(j, heightMap[i - 1][j], i - 1);
                    glEnd();
                }
            }
        }
    }
    else{
        /*Flat shaded triangles*/
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                /*Draw counterclockwise triangles*/
                if((i < height - 1) && (j > 0)){
                    glBegin(GL_TRIANGLES);
                    
                    /*Normal for the whole triangle*/
                    glNormal3f(triangleNormals[i][( 2*(j-1) ) + 1]->xLen,
                               triangleNormals[i][( 2*(j-1) ) + 1]->yLen,
                               triangleNormals[i][( 2*(j-1) ) + 1]->zLen);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j]);
                    glVertex3f(j, heightMap[i][j], i);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j-1]);
                    glVertex3f(j - 1, heightMap[i][j - 1], i);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i+1][j]);
                    glVertex3f(j, heightMap[i + 1][j], i + 1);
                    glEnd();
                }
                
                if((i > 0) && (j < width - 1)){
                    glBegin(GL_TRIANGLES);
                    
                    /*Normal for the whole triangle*/
                    glNormal3f(triangleNormals[i - 1][( 2*(j) )]->xLen,
                               triangleNormals[i - 1][( 2*(j) )]->yLen,
                               triangleNormals[i - 1][( 2*(j) )]->zLen);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j]);
                    glVertex3f(j, heightMap[i][j], i);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i][j+1]);
                    glVertex3f(j + 1, heightMap[i][j + 1], i);
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuseColourMap[i-1][j]);
                    glVertex3f(j, heightMap[i - 1][j], i - 1);
                    glEnd();
                }
            }
        }
    }
    
    glDisable(GL_NORMALIZE);
}



