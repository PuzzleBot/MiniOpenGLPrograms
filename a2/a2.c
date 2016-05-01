
/* I may have used too many globals, but most of them were nessasary due to the nature of OpenGL. RIP namespace */

#include "a2.h"

/* flags used to control the appearance of the image */
int lineDrawing = 0;	// draw polygons as solid or lines
int lighting = 1;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading
int colourMode = 0;

/*Information from the file, required to draw the map*/
double ** heightMap = NULL;
GLfloat *** diffuseColourMap = NULL;
Dim3Vector *** vertexNormals = NULL;
Dim3Vector *** triangleNormals = NULL;

int width = 0;
int height = 0;
int depth = 0;

extern double cameraAngle;
extern double cameraZoom;
int previousX = 0;
int previousY = 0;
int mouseDown = NO_MOUSE_DOWN;
double scaleMultiplier = 1;


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
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    } else {
        glLightfv (GL_LIGHT0, GL_AMBIENT, light_full_on);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light_full_off);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
    }
    
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
    
    GLfloat light_position[] = { 0.0, 15.0, 0.0, 0.0 };
    
    /*Viewpoint position and its focal point, adjusted based on zoom and user scaling*/
    double camera[3] = { width/2, (double)DISPLAYHEIGHT*2 - (1*cameraZoom), cameraZoom + 7};
    double focalPoint[3] = { width/2, ((double)DISPLAYHEIGHT/2) * scaleMultiplier, height/2};
    
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
    
    /* Orbit simulation */
    glTranslatef(focalPoint[0], focalPoint[1], focalPoint[2]);
    glRotatef(cameraAngle, 0, 1, 0);
    glTranslatef(-focalPoint[0], -focalPoint[1], -focalPoint[2]);
    
    /*Scale up/down based on depth and the user's modifier (right mouse button), the default max height of the heightmap is 10*/
    glScalef(1, ((double)DISPLAYHEIGHT/(double)depth) * scaleMultiplier, 1);
    
    /* set starting location of objects */
    glPushMatrix ();
    
    /* give all objects the same shininess value */
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);
    
    /* set default colour of heightmap */
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grey);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    drawMap();
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
            freeMapData();
            exit(0);
            break;
        case '0':		// draw polygons as outlines
            lineDrawing = 1;
            lighting = 0;
            smoothShading = 0;
            init();
            display();
            break;
        case '1':		// diffuse and specular lighting, flat shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 0;
            init();
            display();
            break;
        case '2':		// diffuse and specular lighting, smooth shading
            lineDrawing = 0;
            lighting = 1;
            smoothShading = 1;
            init();
            display();
            break;
        case '3':
            toColourScheme(GREY_SCHEME);
            init();
            display();
            break;
        case '4':
            toColourScheme(HEIGHT_SCHEME);
            init();
            display();
            break;
        case '5':
            toColourScheme(RANDOM_SCHEME);
            init();
            display();
            break;
    }
}


void mouseAction(int x, int y){
    /*Click and hold left mouse: Rotate/zoom*/
    if(mouseDown == LEFT_MOUSE_DOWN){
        transformCamera((double)(x - previousX), (double)(y - previousY));
        display();
    }
    else if(mouseDown == RIGHT_MOUSE_DOWN){
        /*Click and hold right mouse: Scale in direction of mouse movement*/
        scaleMultiplier = scaleMultiplier + ((double)(y - previousY)) * 0.1;
        display();
    }
    
    previousX = x;
    previousY = y;
}


void clickAction(int button, int state, int x, int y){
    /*On mouse click, get the initial mouse position*/
    previousX = x;
    previousY = y;
    
    switch(button){
        case GLUT_LEFT_BUTTON:
            mouseDown = LEFT_MOUSE_DOWN;
            break;
        case GLUT_RIGHT_BUTTON:
            mouseDown = RIGHT_MOUSE_DOWN;
        default:
            break;
    }
}


void loadTexture(char * fileName) {
    FILE *fp;
    int  i, j;
    int  red = 255, green = 255, blue = 255;
    
    if ((fp = fopen(fileName, "r")) == 0) {
        printf("Error, failed to find the file specified.\n");
        exit(0);
    }
    
    parseStream(fp);
    
    fclose(fp);
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (1024, 768);
    glutCreateWindow (argv[0]);
    init();
    loadTexture(argv[1]);
    glutReshapeFunc (reshape);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(clickAction);
    glutMotionFunc(mouseAction);
    
    glutMainLoop();
    return 0; 
}

