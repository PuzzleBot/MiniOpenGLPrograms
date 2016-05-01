
/* I may have used too many globals, but most of them were nessasary due to the nature of OpenGL. RIP namespace */

#include "a3.h"

/* flags used to control the appearance of the image */
int lineDrawing = 0;	// draw polygons as solid or lines
int lighting = 1;	// use diffuse and specular lighting
int smoothShading = 1;  // smooth or flat shading
int colourMode = 0;

/*Information from the file, required to draw the texture*/
GLubyte * colourMap = NULL;
int currentTextureID = 0;
unsigned int texNames[NUMBER_OF_TEXTURES] = {0};

double lightAngle = 0.0;

int width = 0;
int height = 0;
int depth = 0;

int previousX = 0;
int previousY = 0;


/*  Initialize material property and light source.
 */
void init (void)
{
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_full_off[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_full_on[] = { 1.0, 1.0, 1.0, 1.0 };
    
    GLfloat light_position[] = { 0.0, 15.0, 0.0, 0.0 };
    
    /* if lighting is turned on then use ambient, diffuse and specular
     lights, otherwise use ambient lighting only */
    if (lighting == 1) {
        glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        //glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
    } else {
        glLightfv (GL_LIGHT0, GL_AMBIENT, light_full_on);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light_full_off);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
    }
    
    glShadeModel(GL_FLAT);
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
    GLfloat grey[]  = {0.5, 0.5, 0.5, 1.0};
    
    GLfloat light_position[] = { -10.0, 15.0, -8.0, 0.0 };
    
    /*Viewpoint position and its focal point, adjusted based on zoom and user scaling*/
    double camera[3] = { -(LENGTH * 2 * 1.5), (double)LENGTH * 3, -(LENGTH * 3 * 1.5)};
    double focalPoint[3] = { ((double)(LENGTH / 2)), ((double)(LENGTH / 2)), ((double)(LENGTH / 2))};
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* draw surfaces as either smooth or flat shaded */
    if (smoothShading == 1)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);
    
    /* draw polygons as either solid or outlines (left in here as key 0, just to see the mesh)*/
    if (lineDrawing == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    /* Simulate camera orbit and zoom by rotating/moving the whole scene before drawing it */
    glPushMatrix();
    gluLookAt(camera[0], camera[1], camera[2], focalPoint[0], focalPoint[1], focalPoint[2], 0, 1, 0);
    
    /* set starting location of objects */
    glPushMatrix ();
    
    /* give all objects the same shininess value */
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    
    /* set default colour of heightmap */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grey);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    drawScene();
    glPopMatrix ();
    
    glPopMatrix();
    
    glFlush ();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            break;
        case 'q':
            exit(0);
            break;
        case '0':		// draw polygons as outlines
            lineDrawing = 1;
            lighting = 0;
            smoothShading = 0;
            init();
            display();
            break;
        case '1':		// diffuse and specular lighting, flat shading, swap textures
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 1;
            
            currentTextureID++;
            if(currentTextureID >= NUMBER_OF_TEXTURES){
                currentTextureID = 0;
            }
            
            init();
            display();
            break;
    }
}


void timerDisplay(){
    sleep(0);
    display();
}


void loadTexture(char * fileName, int textureID) {
    FILE *fp;
    int i, j, c;
    
    if ((fp = fopen(fileName, "r")) == 0) {
        printf("Error, failed to find the \"%s\".\n", fileName);
        exit(0);
    }
    
    parseStream(fp);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texNames[textureID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, colourMap);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    
    fclose(fp);
}


void loadAllTextures(){
    glGenTextures(NUMBER_OF_TEXTURES, texNames);
    
    loadTexture("images/brick.ppm", 0);
    loadTexture("images/horrible.ppm", 1);
    loadTexture("images/moon.ppm", 2);
    loadTexture("images/mud.ppm", 3);
    loadTexture("images/psych.ppm", 4);
    loadTexture("images/spots.ppm", 5);
    loadTexture("images/wood.ppm", 6);
    
}


/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (1024, 768);
    glutCreateWindow (argv[0]);
    init();
    loadAllTextures();
    glutReshapeFunc(reshape);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(timerDisplay);
    
    glutMainLoop();
    return 0; 
}

