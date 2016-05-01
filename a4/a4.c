/* Derived from scene.c in the The OpenGL Programming Guide */

#include "a4.h"

/* flags used to control the appearance of the image */
int lineDrawing = 1;	// draw polygons as solid or lines
int lighting = 0;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading
int textures = 0;

LightData lightSource;
SphereData * spheres;
int numberOfSpheres = 0;

GLfloat * pixelData;
int width = START_WIDTH;
int height = START_HEIGHT;

/*Viewpoint coordinates*/
long double viewpointX;
long double viewpointY;
long double viewpointZ;



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
}

void display (void)
{
    GLfloat blue[]  = {0.0, 0.0, 1.0, 1.0};
    GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
    GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    
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
    
    /* set starting location of objects */
    glPushMatrix ();
    
    /* give all objects the same shininess value */
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    
    drawPixels();
    
    glPopMatrix ();
    glFlush ();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 10.0);
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
            textures = 0;
            init();
            display();
            break;
        case '2':		// draw polygons as filled
            lineDrawing = 0;
            lighting = 0;
            smoothShading = 0;
            textures = 0;
            init();
            display();
            break;
        case '3':		// diffuse and specular lighting, flat shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 0;
            textures = 0;
            init();
            display();
            break;
        case '4':		// diffuse and specular lighting, smooth shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 1;
            textures = 0;
            init();
            display();
            break;
        case '5':		// texture with  smooth shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 1;
            textures = 1;
            init();
            display();
            break;
    }
}

void loadTexture(char * fileName) {
    FILE *fp;
    int  i, j;
    int  red, green, blue;
    
    if ((fp = fopen(fileName, "r")) == 0) {
        printf("Error, failed to find the file named %s.\n", fileName);
        exit(0);
    }
    
    parseFile(fp);
    
    fclose(fp);
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    viewpointX = ((START_WIDTH / PIXELS_PER_UNIT) / 2);
    viewpointY = ((START_HEIGHT / PIXELS_PER_UNIT) / 2);
    viewpointZ = -((START_WIDTH / PIXELS_PER_UNIT) / 2);
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (START_WIDTH, START_HEIGHT);
    glutCreateWindow (argv[0]);
    init();
    loadTexture(argv[1]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc (keyboard);
    glutMainLoop();
    return 0; 
}

