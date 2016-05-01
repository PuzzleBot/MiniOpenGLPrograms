#include "a1.h"

extern int numberLevels;

ObjectData objectData[10];


void parseStream(FILE * inputFile){
    int i;
    int lineCount = 0;
    char currentString[500];
    char * currentToken = NULL;
    
    fgets(currentString, 500, inputFile);
    
    fgets(currentString, 500, inputFile);
    while((feof(inputFile) == 0) && (ferror(inputFile) == 0)){
        for(i = 0; i < 22; i++){
            if(i == 0){
                currentToken = strtok(currentString, " \t\n");
            }
            else{
                currentToken = strtok(NULL, " \t\n");
            }
            
            switch(i){
                case 0:
                    objectData[lineCount].shape = atoi(currentToken);
                    break;
                case 1:
                    objectData[lineCount].colour = atoi(currentToken);
                    break;
                case 2:
                    objectData[lineCount].iterations = atoi(currentToken);
                    break;
                case 3:
                    objectData[lineCount].size = atof(currentToken);
                    break;
                case 4:
                    objectData[lineCount].inx = atof(currentToken);
                    break;
                case 5:
                    objectData[lineCount].xoff = atof(currentToken);
                    break;
                case 6:
                    objectData[lineCount].iny = atof(currentToken);
                    break;
                case 7:
                    objectData[lineCount].yoff = atof(currentToken);
                    break;
                case 8:
                    objectData[lineCount].inz = atof(currentToken);
                    break;
                case 9:
                    objectData[lineCount].zoff = atof(currentToken);
                    break;
                case 10:
                    objectData[lineCount].inxr = atof(currentToken);
                    break;
                case 11:
                    objectData[lineCount].xroff = atof(currentToken);
                    break;
                case 12:
                    objectData[lineCount].inyr = atof(currentToken);
                    break;
                case 13:
                    objectData[lineCount].yroff = atof(currentToken);
                    break;
                case 14:
                    objectData[lineCount].inzr = atof(currentToken);
                    break;
                case 15:
                    objectData[lineCount].zroff = atof(currentToken);
                    break;
                case 16:
                    objectData[lineCount].inxs = atof(currentToken);
                    break;
                case 17:
                    objectData[lineCount].xsoff = atof(currentToken);
                    break;
                case 18:
                    objectData[lineCount].inys = atof(currentToken);
                    break;
                case 19:
                    objectData[lineCount].ysoff = atof(currentToken);
                    break;
                case 20:
                    objectData[lineCount].inzs = atof(currentToken);
                    break;
                case 21:
                    objectData[lineCount].zsoff = atof(currentToken);
                    break;
                default:
                    printf("Error: Unrecognized parameter.\n");
                    exit(0);
                    break;
            }
        }

        /*printf("Shape %d\n", lineCount);
        printObject(objectData[lineCount]);*/
        lineCount++;
        
        fgets(currentString, 500, inputFile);
    }
    numberLevels = lineCount;
}

void deleteNewline(char * str){
    int currentChar = 0;
    
    while(str[currentChar] != '\0'){
        if(str[currentChar] == '\n'){
            str[currentChar] = '\0';
        }
        currentChar++;
    }
}

void printObject(ObjectData object){
    printf("Shape: %d\n", object.shape);
    printf("Colour: %d\n", object.colour);
    printf("Iterations: %d\n", object.iterations);
    printf("Size: %.2f\n\n", object.size);
    
    printf("inx: %.2f\n", object.inx);
    printf("xoff: %.2f\n", object.xoff);
    printf("iny: %.2f\n", object.iny);
    printf("yoff: %.2f\n", object.yoff);
    printf("inz: %.2f\n", object.inz);
    printf("zoff: %.2f\n\n", object.zoff);
    
    printf("inxr: %.2f\n", object.inxr);
    printf("xroff: %.2f\n", object.xroff);
    printf("inyr: %.2f\n", object.inyr);
    printf("yroff: %.2f\n", object.yroff);
    printf("inzr: %.2f\n", object.inzr);
    printf("zroff: %.2f\n\n", object.zroff);
    
    printf("inxs: %.2f\n", object.inxs);
    printf("xsoff: %.2f\n", object.xsoff);
    printf("inys: %.2f\n", object.inys);
    printf("ysoff: %.2f\n", object.ysoff);
    printf("inzs: %.2f\n", object.inzs);
    printf("zsoff: %.2f\n\n", object.zsoff);
}


