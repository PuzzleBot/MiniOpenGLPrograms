#include "a3.h"

extern GLubyte * colourMap;

extern int width;
extern int height;
extern int depth;


void parseStream(FILE * fp){
    char currentString[2048];
    char * token = NULL;
    
    double initColour[] = GREY;
    
    int initParamCount = 0;
    int currentIndex = 0;
    
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
                        
                        /*All input parameters found, allocate memory*/
                        colourMap = calloc(height * width * 3, sizeof(GLubyte));
                        
                        if(colourMap == NULL){
                            printf("Not enough memory.\n");
                            exit(1);
                        }
                        break;
                    default:
                        /*Get data*/
                        /*This works like a nested for loop written in a weird way to accomodate for \n being allowed to be used like a single space*/
                        
                        colourMap[currentIndex] = (GLubyte)atoi(token);
                        currentIndex++;
                        break;
                }
                token = strtok(NULL, WHITESPACE);
            }
        }
        fgets(currentString, 2048, fp);
    }
}


void printColourMap(){
    int i;
    int j;
    
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            printf("%d %d %d,  ", colourMap[(i * height) + (4 * width)], colourMap[(i * height) + (4 * width) + 1], colourMap[(i * height) + (4 * width) + 2]);
        }
        printf("\n");
    }
}
