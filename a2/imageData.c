#include "a2.h"

extern double ** heightMap;
extern GLfloat *** diffuseColourMap;
extern Dim3Vector *** vertexNormals;
extern Dim3Vector *** triangleNormals;

extern int width;
extern int height;
extern int depth;

extern double cameraZoom;

void parseStream(FILE * fp){
    char currentString[2048];
    char * token = NULL;
    
    double initColour[] = GREY;
    
    int initParamCount = 0;
    int currentHeight = 0;
    int currentWidth = 0;
    
    int i;
    int j;
    
    /*Throw out the first line*/
    fgets(currentString, 2048, fp);
    
    fgets(currentString, 2048, fp);
    while((feof(fp) == 0) && (ferror(fp) == 0)){
        if(currentString[0] == '#'){
            /* Ignore comment */
        }
        else{
            token = strtok(currentString, WHITESPACE);
            while(token != NULL){
                switch(initParamCount){
                    /* Find width, height and depth, then get data */
                    case 0:
                        width = atoi(token);
                        initParamCount++;
                        break;
                    case 1:
                        height = atoi(token);
                        initParamCount++;
                        break;
                    case 2:
                        depth = atoi(token);
                        initParamCount++;
                        
                        /*All input parameters found, allocate heightmap memory*/
                        heightMap = calloc(height, sizeof(double *));
                        diffuseColourMap = calloc(height, sizeof(GLfloat **));
                        vertexNormals = calloc(height, sizeof(Dim3Vector **));
                        triangleNormals = calloc((height - 1), sizeof(Dim3Vector **));
                        
                        if((heightMap == NULL) || (vertexNormals == NULL) || (triangleNormals == NULL) || (diffuseColourMap == NULL)){
                            printf("Not enough memory.\n");
                            exit(1);
                        }
                        
                        for(i = 0; i < height; i++){
                            heightMap[i] = calloc(width, sizeof(double));
                            diffuseColourMap[i] = calloc(width, sizeof(GLfloat *));
                            vertexNormals[i] = calloc(width, sizeof(Dim3Vector *));
        
                            if((heightMap[i] == NULL) || (vertexNormals[i] == NULL) || (diffuseColourMap[i] == NULL)){
                                printf("Not enough memory.\n");
                                exit(1);
                            }
                            
                            /*Initialize colour map to be grey everywhere*/
                            for(j = 0; j < width; j++){
                                diffuseColourMap[i][j] = calloc(4, sizeof(GLfloat));
                                
                                if(diffuseColourMap[i][j] == NULL){
                                    printf("Not enough memory.\n");
                                    exit(1);
                                }
                                
                                diffuseColourMap[i][j][0] = initColour[0];
                                diffuseColourMap[i][j][1] = initColour[1];
                                diffuseColourMap[i][j][2] = initColour[2];
                                diffuseColourMap[i][j][3] = initColour[3];
                            }
                        }
                        
                        for(i = 0; i < height-1; i++){
                            triangleNormals[i] = calloc((width - 1) * 2, sizeof(Dim3Vector *));
                            if(triangleNormals[i] == NULL){
                                triangleNormals[i] = calloc((width - 1) * 2, sizeof(Dim3Vector *));
                            }
                        }
                        break;
                    default:
                        /*Get data*/
                        /*This works like a nested for loop written in a weird way to accomodate for \n being allowed to be used like a single space*/
                        
                        heightMap[currentHeight][currentWidth] = atoi(token);
                        currentWidth++;
                        if(currentWidth == width){
                            currentWidth = 0;
                            currentHeight++;
                        }
                        break;
                }
                token = strtok(NULL, WHITESPACE);
            }
        }
        fgets(currentString, 2048, fp);
    }
    cameraZoom = -width/2;
}


void freeMapData(){
    int i;
    int j;
    
    if(heightMap != NULL){
        for(i = 0; i < height; i++){
            if(heightMap[i] != NULL){
                free(heightMap[i]);
            }
        }
        free(heightMap);
    }
    
    if(vertexNormals != NULL){
        for(i = 0; i < height; i++){
            if(vertexNormals[i] != NULL){
                for(j = 0; j < width; j++){
                    if(vertexNormals[i][j] != NULL){
                        free(vertexNormals[i][j]);
                    }
                }
                free(vertexNormals[i]);
            }
        }
        free(vertexNormals);
    }
    
    if(diffuseColourMap != NULL){
        for(i = 0; i < height; i++){
            if(diffuseColourMap[i] != NULL){
                for(j = 0; j < width; j++){
                    if(diffuseColourMap[i][j] != NULL){
                        free(diffuseColourMap[i][j]);
                    }
                }
                free(diffuseColourMap[i]);
            }
        }
        free(diffuseColourMap);
    }

    if(triangleNormals != NULL){
        for(i = 0; i < height - 1; i++){
            if(triangleNormals[i] != NULL){
                for(j = 0; j < (width-1)*2; j++){
                    if(triangleNormals[i][j] != NULL){
                        free(triangleNormals[i][j]);
                    }
                }
                free(triangleNormals[i]);
            }
        }
        free(triangleNormals);
    }
}

/*Create a vector*/
Dim3Vector * createVector(double xLen, double yLen, double zLen){
    Dim3Vector * newVector = calloc(1, sizeof(Dim3Vector));
    
    newVector->xLen = xLen;
    newVector->yLen = yLen;
    newVector->zLen = zLen;
    
    return(newVector);
}

/*Create a vector that's a cross product of two vectors*/
Dim3Vector * crossProduct(Dim3Vector * vector1, Dim3Vector * vector2){
    Dim3Vector * newVector = calloc(1, sizeof(Dim3Vector));
    
    newVector->xLen = (vector1->yLen * vector2->zLen) - (vector1->zLen * vector2->yLen);
    newVector->yLen = (vector1->zLen * vector2->xLen) - (vector1->xLen * vector2->zLen);
    newVector->zLen = (vector1->xLen * vector2->yLen) - (vector1->yLen * vector2->xLen);
    
    return(newVector);
}

/*Convert a vector to a unit vector*/
Dim3Vector * toUnitVector(Dim3Vector * vector){
    double vecMagnitude = sqrt(pow(vector->xLen, 2) + pow(vector->yLen, 2) + pow(vector->zLen, 2));
    
    vector->xLen = vector->xLen / vecMagnitude;
    vector->yLen = vector->yLen / vecMagnitude;
    vector->zLen = vector->zLen / vecMagnitude;
    
    return(vector);
    
}

/*Average an array of n vectors*/
Dim3Vector * averageVectors(Dim3Vector ** vectorList, int numberOfVectors){
    Dim3Vector * newVector = calloc(1, sizeof(Dim3Vector));
    int i;
    
    newVector->xLen = 0;
    newVector->yLen = 0;
    newVector->zLen = 0;
    
    for(i = 0; i < numberOfVectors; i++){
        newVector->xLen = newVector->xLen + vectorList[i]->xLen;
        newVector->yLen = newVector->yLen + vectorList[i]->yLen;
        newVector->zLen = newVector->zLen + vectorList[i]->zLen;
    }
    
    newVector->xLen = newVector->xLen/(double)numberOfVectors;
    newVector->yLen = newVector->yLen/(double)numberOfVectors;
    newVector->zLen = newVector->zLen/(double)numberOfVectors;
    
    return(newVector);
}

/*Calculate all needed normals for the heightmap (heightmap is assumed to be 2x2 or larger)*/
void calculateNormals(){
    int i;
    int j;
    
    Dim3Vector crossVect1;
    Dim3Vector crossVect2;
    Dim3Vector * involvedVectors[8];
    
    if(width == 0 || height == 0){
        return;
    }
    
    /*Calculate normals for each triangle*/
    for(i = 0; i < height - 1; i++){
        for(j = 0; j < width - 1; j++){
            /*Two triangles connected at the bottom-right of each vertex*/
            crossVect1.xLen = 0;
            crossVect1.yLen = heightMap[i+1][j] - heightMap[i][j];
            crossVect1.zLen = 1;
            
            crossVect2.xLen = 1;
            crossVect2.yLen = heightMap[i+1][j+1] - heightMap[i][j];
            crossVect2.zLen = 1;
            
            triangleNormals[i][2*j] = crossProduct(&crossVect1, &crossVect2);
            toUnitVector(triangleNormals[i][2*j]);
            
            
            crossVect1.xLen = 1;
            crossVect1.yLen = heightMap[i][j+1] - heightMap[i][j];
            crossVect1.zLen = 0;
            
            crossVect2.xLen = 1;
            crossVect2.yLen = heightMap[i+1][j+1] - heightMap[i][j];
            crossVect2.zLen = 1;
            
            triangleNormals[i][(2*j) +1] = crossProduct(&crossVect1, &crossVect2);
            triangleNormals[i][(2*j) +1]->xLen = -(triangleNormals[i][(2*j) +1]->xLen);
            triangleNormals[i][(2*j) +1]->yLen = -(triangleNormals[i][(2*j) +1]->yLen);
            triangleNormals[i][(2*j) +1]->zLen = -(triangleNormals[i][(2*j) +1]->zLen);
            toUnitVector(triangleNormals[i][(2*j) +1]);
        }
    }
    
    /*Vertex Normals - Average the normals of surrounding triangles*/
    /*Top left corner vertex*/
    involvedVectors[0] = triangleNormals[0][0];
    involvedVectors[1] = triangleNormals[0][1];
    
    vertexNormals[0][0] = toUnitVector(averageVectors(involvedVectors, 2));
    
    /*Top Right corner vertex*/
    involvedVectors[0] = triangleNormals[0][(2*(width - 2)) + 1];
    
    vertexNormals[0][width-1] = toUnitVector(averageVectors(involvedVectors, 1));
    
    /*Bottom left corner vertex*/
    involvedVectors[0] = triangleNormals[height-2][0];
    
    vertexNormals[height-1][0] = toUnitVector(averageVectors(involvedVectors, 1));
    
    /*Bottom Right corner vertex*/
    involvedVectors[0] = triangleNormals[height-2][(2*(width - 2))];
    involvedVectors[1] = triangleNormals[height-2][(2*(width - 2)) + 1];
    
    vertexNormals[height-1][width-1] = toUnitVector(averageVectors(involvedVectors, 2));
    
    for(i = 1; i < height - 1; i++){
        /*Left edge vertices*/
        involvedVectors[0] = triangleNormals[i-1][0];
        involvedVectors[1] = triangleNormals[i][0];
        involvedVectors[2] = triangleNormals[i][1];
        
        vertexNormals[i][0] = toUnitVector(averageVectors(involvedVectors, 3));
        
        /*Right edge vertices*/
        involvedVectors[0] = triangleNormals[i-1][(2*(width - 2))];
        involvedVectors[1] = triangleNormals[i-1][(2*(width - 2)) + 1];
        involvedVectors[2] = triangleNormals[i][(2*(width - 2)) + 1];
        
        vertexNormals[i][width-1] = toUnitVector(averageVectors(involvedVectors, 3));
    }
    
    for(j = 1; j < width - 1; j++){
        /*Top edge vertices*/
        involvedVectors[0] = triangleNormals[0][2*(j-1) + 1];
        involvedVectors[1] = triangleNormals[0][2*j];
        involvedVectors[2] = triangleNormals[0][(2*j) + 1];
        
        vertexNormals[0][j] = toUnitVector(averageVectors(involvedVectors, 3));
        
        /*Bottom edge vertices*/
        involvedVectors[0] = triangleNormals[height-2][2*(j-1)];
        involvedVectors[1] = triangleNormals[height-2][2*(j-1) + 1];
        involvedVectors[2] = triangleNormals[height-2][2*j];
        
        vertexNormals[height-1][j] = toUnitVector(averageVectors(involvedVectors, 3));
    }
    
    for(i = 1; i < height - 1; i++){
        for(j = 1; j < width - 1; j++){
            involvedVectors[0] = triangleNormals[i-1][(2*(j-1))];
            involvedVectors[1] = triangleNormals[i-1][(2*(j-1)) + 1];
            involvedVectors[2] = triangleNormals[i-1][(2*j)];
            involvedVectors[3] = triangleNormals[i][(2*(j-1)) + 1];
            involvedVectors[4] = triangleNormals[i][(2*j)];
            involvedVectors[5] = triangleNormals[i][(2*j) + 1];
            
            vertexNormals[i][j] = toUnitVector(averageVectors(involvedVectors, 6));
        }
    }
}

void printVertexNormals(){
    int i;
    int j;
    
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            printf("vn(%d,%d):[%.2f, %.2f, %.2f] ", i, j, vertexNormals[i][j]->xLen, vertexNormals[i][j]->yLen, vertexNormals[i][j]->zLen);
        }
        printf("\n");
    }
}

/*Scheme must be one of GREY_SCHEME, HEIGHT_SCHEME, or RANDOM_SCHEME*/
void toColourScheme(int scheme){
    int i;
    int j;
    
    GLfloat randomRedChange = 0.0;
    GLfloat randomGreenChange = 0.0;
    GLfloat randomBlueChange = 0.0;
    
    GLfloat grey[] = GREY;
    GLfloat white[] = WHITE;
    GLfloat green[] = GREEN;
    GLfloat brown[] = BROWN;
    
    double minWhiteY = (2 * (double)depth) / 3;
    double minGreenY = ((double)depth) / 3;
    
    switch(scheme){
        case GREY_SCHEME:
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    diffuseColourMap[i][j][0] = grey[0];
                    diffuseColourMap[i][j][1] = grey[1];
                    diffuseColourMap[i][j][2] = grey[2];
                    diffuseColourMap[i][j][3] = grey[3];
                }
            }
            break;
        case HEIGHT_SCHEME:
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    if(heightMap[i][j] >= minWhiteY){
                        diffuseColourMap[i][j][0] = white[0];
                        diffuseColourMap[i][j][1] = white[1];
                        diffuseColourMap[i][j][2] = white[2];
                        diffuseColourMap[i][j][3] = white[3];
                    }
                    else if(heightMap[i][j] >= minGreenY){
                        diffuseColourMap[i][j][0] = green[0];
                        diffuseColourMap[i][j][1] = green[1];
                        diffuseColourMap[i][j][2] = green[2];
                        diffuseColourMap[i][j][3] = green[3];
                    }
                    else{
                        diffuseColourMap[i][j][0] = brown[0];
                        diffuseColourMap[i][j][1] = brown[1];
                        diffuseColourMap[i][j][2] = brown[2];
                        diffuseColourMap[i][j][3] = brown[3];
                    }
                }
            }
            break;
        case RANDOM_SCHEME:
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    /*Randomize change for each colour between -0.1 and 0.1*/
                    randomRedChange = ((GLfloat)(rand() % 200)) - 100;
                    randomGreenChange = ((GLfloat)(rand() % 200)) - 100;
                    randomBlueChange = ((GLfloat)(rand() % 200)) - 100;
                    
                    randomRedChange = randomRedChange / 1000;
                    randomGreenChange = randomGreenChange / 1000;
                    randomBlueChange = randomBlueChange / 1000;
                    
                    diffuseColourMap[i][j][0] = diffuseColourMap[i][j][0] + randomRedChange;
                    diffuseColourMap[i][j][1] = diffuseColourMap[i][j][1] + randomGreenChange;
                    diffuseColourMap[i][j][2] = diffuseColourMap[i][j][2] + randomBlueChange;
                    diffuseColourMap[i][j][3] = 1.0;
                    
                    if(diffuseColourMap[i][j][0] > 1){
                        diffuseColourMap[i][j][0] = 1.0;
                    }
                    else if(diffuseColourMap[i][j][0] < 0){
                        diffuseColourMap[i][j][0] = 0.0;
                    }

                    if(diffuseColourMap[i][j][1] > 1){
                        diffuseColourMap[i][j][1] = 1.0;
                    }
                    else if(diffuseColourMap[i][j][1] < 0){
                        diffuseColourMap[i][j][1] = 0.0;
                    }
                    
                    if(diffuseColourMap[i][j][2] > 1){
                        diffuseColourMap[i][j][2] = 1.0;
                    }
                    else if(diffuseColourMap[i][j][2] < 0){
                        diffuseColourMap[i][j][2] = 0.0;
                    }
                }
            }
            break;
        default:
            break;
    }
}
