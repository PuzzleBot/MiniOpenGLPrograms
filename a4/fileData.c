#include "a4.h"

extern LightData lightSource;
extern SphereData * spheres;

extern int numberOfSpheres;

/*File must end with newline*/
void parseFile(FILE * fp){
    char inputBuffer[2048];
    char * token = NULL;
    
    fgets(inputBuffer, 2048, fp);
    token = strtok(inputBuffer, WHITESPACE);
    
    /*Get light parameters*/
    token = strtok(NULL, WHITESPACE);
    lightSource.pos.x = atof(token);
    
    token = strtok(NULL, WHITESPACE);
    lightSource.pos.y = atof(token);
    
    token = strtok(NULL, WHITESPACE);
    lightSource.pos.z = atof(token);
    
    token = strtok(NULL, WHITESPACE);
    lightSource.r = atof(token);
    
    token = strtok(NULL, WHITESPACE);
    lightSource.g = atof(token);
    
    token = strtok(NULL, WHITESPACE);
    lightSource.b = atof(token);
    
    lightSource.attenuation = ATTENUATION;
    
    /*Get sphere data*/
    fgets(inputBuffer, 2048, fp);
    token = strtok(inputBuffer, WHITESPACE);
    
    while((feof(fp) == 0) && (ferror(fp) == 0)){
        if(token != NULL){
            numberOfSpheres++;
            spheres = reallocf(spheres, sizeof(SphereData) * numberOfSpheres);
            if(spheres == NULL){
                printf("Not enough memory.\n");
                exit(1);
            }
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].pos.x = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].pos.y = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].pos.z = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].radius = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].r = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].g = atof(token);
            
            token = strtok(NULL, WHITESPACE);
            spheres[numberOfSpheres - 1].b = atof(token);
        }
        
        fgets(inputBuffer, 2048, fp);
        token = strtok(inputBuffer, WHITESPACE);
    }
}
