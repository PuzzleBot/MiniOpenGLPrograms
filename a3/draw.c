#include "a3.h"

extern GLubyte * colourMap;

extern int width;
extern int height;
extern int depth;

extern int currentTextureID;
extern unsigned int texNames[NUMBER_OF_TEXTURES];

extern double lightAngle;

void drawScene(){
    
    GLfloat light_position[4] = { 0.0, 0.0, 0.0, 1.0 };
    double center[] = {LENGTH/2, LENGTH/2, LENGTH/2};
    
    GLfloat cubeColour[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat planeColour[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightColour[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat buffer[2] = {0.0};
    int i;
    int j;
    
    /*Place the light source*/
    glPushMatrix();
    lightAngle = lightAngle + 2.5;
    
    if(lightAngle >= (360)){
        lightAngle = lightAngle - (360);
    }
    else if(lightAngle <= (-360)){
        lightAngle = lightAngle + (360);
    }
    
    /*Rotation and translation as a translation for the light's position*/
    glTranslatef(LIGHT_RADIUS * cos((lightAngle) * (M_PI / 180)), LENGTH * 1.5, LIGHT_RADIUS * sin((lightAngle) * (M_PI / 180)));
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_EMISSION, lightColour);
    glutSolidSphere(1, 15, 15);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cubeColour);
    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[currentTextureID]);
    
    for(i = 0; i < LENGTH; i++){
        for(j = 0; j < LENGTH; j++){
            /*Draw the front square*/
            glBegin(GL_QUADS);
            glNormal3f(-1, 0, 0);
            
            glTexCoord2f( (((GLfloat)j )/LENGTH),( ((GLfloat)i )/LENGTH));
            glVertex3i(0, i, j);
            
            glTexCoord2f( ((GLfloat)j + 1.0 )/LENGTH,( ((GLfloat)i)/LENGTH));
            glVertex3i(0, i, j+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(0, i+1, j+1);
            
            glTexCoord2f( ((GLfloat)j)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(0, i+1, j);
            glEnd();
            
            /*Draw the left square*/
            glBegin(GL_QUADS);
            glNormal3f(0, 0, -1);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j, i, 0);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j, i+1, 0);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j+1, i+1, 0);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j+1, i, 0);
            glEnd();
            
            /*Draw the right square*/
            glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j, i, LENGTH);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j, i+1, LENGTH);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j+1, i+1, LENGTH);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j+1, i, LENGTH);
            glEnd();
            
            /*Draw the top square*/
            glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j, LENGTH, i);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j, LENGTH, i+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j+1, LENGTH, i+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j+1, LENGTH, i);
            glEnd();
            
            /*Draw the bottom square*/
            glBegin(GL_QUADS);
            glNormal3f(0, -1, 0);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH, ( ((GLfloat)i )/LENGTH));
            glVertex3i(j, 0, i);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH, ( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j, 0, i+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(j+1, 0, i+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(j+1, 0, i);
            glEnd();
            
            /*Draw the back square*/
            glBegin(GL_QUADS);
            glNormal3f(1, 0, 0);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(LENGTH, i, j);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i )/LENGTH));
            glVertex3i(LENGTH, i, j+1);
            
            glTexCoord2f( ((GLfloat)j + 1.0)/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(LENGTH, i+1, j+1);
            
            glTexCoord2f( ((GLfloat)j )/LENGTH,( ((GLfloat)i + 1.0)/LENGTH));
            glVertex3i(LENGTH, i+1, j);
            glEnd();
        }
    }
    
    glDisable(GL_TEXTURE_2D);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planeColour);
    
    /*Draw the bottom plane*/
    glNormal3f(0, 1, 0);
    glPushMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    for(i = -NUMBER_OF_DIVISIONS; i < NUMBER_OF_DIVISIONS - 1; i++){
        for(j = -NUMBER_OF_DIVISIONS; j < NUMBER_OF_DIVISIONS - 1; j++){
            glBegin(GL_QUADS);
            
            glNormal3f(0, 1, 0);
            glVertex3i(j*PLANE_MULTIPLIER,     0,     i*PLANE_MULTIPLIER);
            glNormal3f(0, 1, 0);
            glVertex3i((j+1)*PLANE_MULTIPLIER, 0,     i*PLANE_MULTIPLIER);
            glNormal3f(0, 1, 0);
            glVertex3i((j+1)*PLANE_MULTIPLIER, 0, (i+1)*PLANE_MULTIPLIER);
            glNormal3f(0, 1, 0);
            glVertex3i(j*PLANE_MULTIPLIER,     0, (i+1)*PLANE_MULTIPLIER);
            
            glEnd();
        }
    }
    glPopMatrix();
    
    drawFakeShadow(LIGHT_RADIUS * cos((lightAngle) * (M_PI / 180)), 15.0, LIGHT_RADIUS * sin((lightAngle) * (M_PI / 180)));
}


void drawFakeShadow(GLfloat lightPosX, GLfloat lightPosY, GLfloat lightPosZ){
    GLfloat shadowMatrix[] = { lightPosY,          0,          0,         0,
                              -lightPosX,          0, -lightPosZ,        -1,
                                       0,          0,  lightPosY,         0,
                                       0,          0,          0, lightPosY};
    
    GLfloat shadowColour[]  = {0.1, 0.1, 0.1, 1.0};
    GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
    
    glPushMatrix();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, shadowColour);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
    glMultMatrixf(shadowMatrix);
    
    /*Draw the front square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, LENGTH);
    glVertex3i(0, LENGTH, LENGTH);
    glVertex3i(0, LENGTH, 0);
    glEnd();
    
    /*Draw the left square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, LENGTH, 0);
    glVertex3i(LENGTH, LENGTH, 0);
    glVertex3i(LENGTH, 0, 0);
    glEnd();
    
    /*Draw the right square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(0, 0, LENGTH);
    glVertex3i(0, LENGTH, LENGTH);
    glVertex3i(LENGTH, LENGTH, LENGTH);
    glVertex3i(LENGTH, 0, LENGTH);
    glEnd();
    
    /*Draw the top square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(0, LENGTH, 0);
    glVertex3i(0, LENGTH, LENGTH);
    glVertex3i(LENGTH, LENGTH, LENGTH);
    glVertex3i(LENGTH, LENGTH, 0);
    glEnd();
    
    /*Draw the bottom square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, LENGTH);
    glVertex3i(LENGTH, 0, LENGTH);
    glVertex3i(LENGTH, 0, 0);
    glEnd();
    
    /*Draw the back square*/
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3i(LENGTH, 0, 0);
    glVertex3i(LENGTH, 0, LENGTH);
    glVertex3i(LENGTH, LENGTH, LENGTH);
    glVertex3i(LENGTH, LENGTH, 0);
    glEnd();

    
    glPopMatrix();
}

