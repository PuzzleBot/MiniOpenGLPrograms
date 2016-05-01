#include "a1.h"

/* number of lines in the input file */
int numberLevels;

/* flags used to control the appearance of the image */
int lineDrawing = 1;	// draw polygons as solid or lines
int lighting = 0;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading

extern ObjectData objectData[10];


/*  Initialize material property and light source.
 */
void init (void)
{
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_full_off[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_full_on[] = {1.0, 1.0, 1.0, 1.0};
    
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    
    /* if lighting is turned on then use ambient, diffuse and specular
     lights, otherwise use ambient lighting only */
    if (lighting == 1) {
        glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    } else {
        glLightfv (GL_LIGHT0, GL_AMBIENT, light_full_on);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light_full_off);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
    }
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    /* needed to correct lightin when glScalef() isn't == 1 */
    glEnable(GL_NORMALIZE);
}

/* level is number of entries in the file, numits is the number of interations for each entry (column 3 on each
	line in the file  */
void drawObjects(int level, int numits) {
    GLfloat blue[]  = {0.0, 0.0, 1.0, 1.0};
    GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
    GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    int i;
    
    /* example of drawing an object */
    
    if(level >= numberLevels){
        return;
    }
    
    
    glPushMatrix();
    for(i = 0; i < objectData[level].iterations; i++){
        /* set colour */
        switch(objectData[level].colour){
            case 0:
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
                break;
            case 1:
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
                break;
            case 2:
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
                break;
            case 3:
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
                break;
            default:
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
                break;
        
        }
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);

        /* move to location for object then draw it */
    
        if(i == 0){
            /*Initial transformation*/
            glTranslatef(objectData[level].inx, objectData[level].iny, objectData[level].inz);
            
            glRotatef(objectData[level].inxr, 1, 0, 0);
            glRotatef(objectData[level].inyr, 0, 1, 0);
            glRotatef(objectData[level].inzr, 0, 0, 1);
            
            glScalef(objectData[level].inxs, objectData[level].inys, objectData[level].inzs);
        }
        else{
            /*Iterative offset transformations*/
            glTranslatef(objectData[level].xoff, objectData[level].yoff, objectData[level].zoff);
            
            glRotatef(objectData[level].xroff, 1, 0, 0);
            glRotatef(objectData[level].yroff, 0, 1, 0);
            glRotatef(objectData[level].zroff, 0, 0, 1);
            
            glScalef(objectData[level].xsoff, objectData[level].ysoff, objectData[level].zsoff);
        }
    
        /* "DRAW!" - Spellslinger, 2015 */
        switch(objectData[level].shape){
            case 0:
                glutSolidSphere(objectData[level].size, 15, 15);
                break;
            case 1:
                glutSolidCube(objectData[level].size);
                break;
            case 2:
                glutSolidTorus(objectData[level].size * 0.5, objectData[level].size, 15, 15);
                break;
            case 3:
                glutSolidCone(objectData[level].size, objectData[level].size, 15, 15);
                break;
            default:
                break;
        }
        
        drawObjects(level + 1, 0);

    }
    glPopMatrix();
    
}


void display (void) {
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* draw surfaces as either smooth or flat shaded */
    if (smoothShading == 1)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);
    
    /* draw polygons as either solid or outlines */
    if (lineDrawing == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    /* give all objects the same shininess value */
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    
    /* set starting location of objects */
    glPushMatrix ();
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -15.0);
    
    /* function which calls transformations and drawing of objects */
    drawObjects(0, 0);
    
    glPopMatrix ();
    
    glFlush ();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 50.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
        case 'q':
            exit(0);
            break;
        case '1':		// draw polygons as outlines
            lineDrawing = 1;
            lighting = 0;
            smoothShading = 0;
            init();
            display();
            break;
        case '2':		// draw polygons as filled
            lineDrawing = 0;
            lighting = 0;
            smoothShading = 0;
            init();
            display();
            break;
        case '3':		// diffuse and specular lighting, flat shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 0;
            init();
            display();
            break;
        case '4':		// diffuse and specular lighting, smooth shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 1;
            init();
            display();
            break;
    }
}


/* read data file and store in arrays */
void readFile(char **argv) {
    FILE *fp;
    char instr[1024];
    int count;
    
    /* open file and print error message if name incorrect */
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR, could not open file.\n");
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    
    /* the code to read the input file goes here */
    parseStream(fp);
    /* numlevels is set to the number of lines in the file not including the first comment line */
    
    fclose(fp);
}


/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    
    readFile(argv);
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (1024, 768);
    glutCreateWindow (argv[0]);
    
    init();
    
    glutReshapeFunc (reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc (keyboard);
    
    glutMainLoop();
    return 0; 
}

