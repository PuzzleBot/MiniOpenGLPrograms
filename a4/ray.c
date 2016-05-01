#include "a4.h"

extern LightData lightSource;
extern SphereData * spheres;
extern int numberOfSpheres;

extern GLfloat * pixelData;
extern int width;
extern int height;

/*Viewpoint coordinates*/
extern long double viewpointX;
extern long double viewpointY;
extern long double viewpointZ;


/*Calculate pixel colour*/
void drawPixels(){
    
    pixelData = calloc(3 * width * height, sizeof(GLfloat));
    calculatePixels();
    
    glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixelData);
    
}

/*y, x, r, g, b*/
void setPixelColour(int rowNum, int colNum, GLfloat red, GLfloat green, GLfloat blue){
    pixelData[(3 * width * (height - rowNum)) + (3 * (width - colNum))] = red;
    pixelData[(3 * width * (height - rowNum)) + ((3 * (width - colNum)) + 1)] = green;
    pixelData[(3 * width * (height - rowNum)) + ((3 * (width - colNum)) + 2)] = blue;
}

void calculatePixels(){
    /*Each screen pixel = one square on the projection plane*/
    /*The projection plane is positioned with its center having the same
      Z-coordinates as the viewpoint, and is positioned on the x and y axis
      with width and height equal to the screen*/
    int i;
    int j;
    int k;
    
    /*Components of the quadratic equation for the ray-sphere intersection*/
    long double quadraticA;
    long double quadraticB;
    long double quadraticC;
    int discriminantSign;
    long double quadraticT1;
    long double quadraticT2;
    
    /*Calculated pixel colour*/
    GLfloat pixelRed = 0;
    GLfloat pixelGreen = 0;
    GLfloat pixelBlue = 0;
    
    /*Ray going from the viewpoint into a pixel on the viewing plane*/
    Dim3Vector currentRay;
    
    /*Position of the pixel on the viewing plane*/
    Dim3Vector pixelPos;
    
    /*Intersection->light vector*/
    Dim3Vector currentLightRay;
    long double lightVecLength;
    
    /*Pointer to the shortest vector, used for determining the first intersection of a ray.*/
    Dim3Vector firstIntersectionVector;
    int frontSphereIndex = -1;
    int frontLightSphereIndex = -1;
    
    /*Vectors N, L, R, V*/
    Dim3Vector firstIntersectionNormal;
    Dim3Vector unitLightRay;
    Dim3Vector reflectVector;
    Dim3Vector reverseViewVector;
    
    /*Dot product of N and L, dot product or R and V for the illumination equation*/
    long double normalLightDotProduct;
    long double reflectViewDotProduct;
    
    /*Viewpoint position*/
    Dim3Vector viewpoint;
    viewpoint.x = viewpointX;
    viewpoint.y = viewpointY;
    viewpoint.z = viewpointZ;
    
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            /*Position the viewing plane*/
            pixelPos.x = viewpoint.x - (((long double)width / PIXELS_PER_UNIT) / 2) + ((long double)j / PIXELS_PER_UNIT);
            pixelPos.y = viewpoint.y - (((long double)height / PIXELS_PER_UNIT) / 2) + ((long double)i / PIXELS_PER_UNIT);
            pixelPos.z = viewpoint.z - (((long double)width / PIXELS_PER_UNIT) / 2);
            
            /*Determine the ray's characteristics*/
            currentRay.x = pixelPos.x - viewpoint.x;
            currentRay.y = pixelPos.y - viewpoint.y;
            currentRay.z = pixelPos.z - viewpoint.z;
            normalize(&currentRay);
            
            /*currentRay = ray direction d
             viewpoint = ray origin o
             spheres[k] = sphere center c*/
            
            frontSphereIndex = determineFirstIntersection(viewpoint, currentRay);
            if(frontSphereIndex != -1){
                firstIntersectionVector = determineIntersection(viewpoint, currentRay, frontSphereIndex);
                
                /*Path to the light source*/
                currentLightRay.x = lightSource.pos.x - firstIntersectionVector.x;
                currentLightRay.y = lightSource.pos.y - firstIntersectionVector.y;
                currentLightRay.z = lightSource.pos.z - firstIntersectionVector.z;
                
                if(isLightBlocked(firstIntersectionVector, currentLightRay, frontSphereIndex) == 0){
                    /*Not blocked - Ambient, diffuse, specular*/

                    /*Vector N*/
                    firstIntersectionNormal.x = (firstIntersectionVector.x - spheres[frontSphereIndex].pos.x) / spheres[frontSphereIndex].radius;
                    firstIntersectionNormal.y = (firstIntersectionVector.y - spheres[frontSphereIndex].pos.y) / spheres[frontSphereIndex].radius;
                    firstIntersectionNormal.z = (firstIntersectionVector.z - spheres[frontSphereIndex].pos.z) / spheres[frontSphereIndex].radius;
                    
                    /*Vector L*/
                    unitLightRay.x = currentLightRay.x;
                    unitLightRay.y = currentLightRay.y;
                    unitLightRay.z = currentLightRay.z;
                    normalize(&unitLightRay);
                    
                    /*N dot L*/
                    normalLightDotProduct = dotProduct(firstIntersectionNormal, unitLightRay);
                    
                    /*Vector R (took an equation from http://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector )*/
                    reflectVector.x = unitLightRay.x - (2 * (normalLightDotProduct) * firstIntersectionNormal.x);
                    reflectVector.y = unitLightRay.y - (2 * (normalLightDotProduct) * firstIntersectionNormal.y);
                    reflectVector.z = unitLightRay.z - (2 * (normalLightDotProduct) * firstIntersectionNormal.z);
                    normalize(&reflectVector);
                    
                    /*Vector V*/
                    reverseViewVector.x = -currentRay.x;
                    reverseViewVector.y = -currentRay.y;
                    reverseViewVector.z = -currentRay.z;
                    normalize(&reverseViewVector);
                    
                    /*R dot V*/
                    reflectViewDotProduct = dotProduct(reflectVector, reverseViewVector);
                    
                    /*Full illumination equation*/
                    pixelRed = AMBIENT_RED * AMBIENT_K * spheres[frontSphereIndex].r
                             + ATTENUATION * lightSource.r
                             * ((DIFFUSE_K * spheres[frontSphereIndex].r * normalLightDotProduct)
                             + (SPECULAR_K * lightSource.r * pow(reflectViewDotProduct, SPECULAR_FINE)));
                    
                    pixelGreen = AMBIENT_GREEN * AMBIENT_K * spheres[frontSphereIndex].g
                               + ATTENUATION * lightSource.g
                               * ((DIFFUSE_K * spheres[frontSphereIndex].g * normalLightDotProduct)
                               + (SPECULAR_K * lightSource.g * pow(reflectViewDotProduct, SPECULAR_FINE)));
                    
                    pixelBlue = AMBIENT_BLUE * AMBIENT_K * spheres[frontSphereIndex].b
                              + ATTENUATION * lightSource.b
                              * ((DIFFUSE_K * spheres[frontSphereIndex].b * normalLightDotProduct)
                              + (SPECULAR_K * lightSource.b * pow(reflectViewDotProduct, SPECULAR_FINE)));
                    
                    setPixelColour(i, j, (GLfloat)pixelRed, (GLfloat)pixelGreen, (GLfloat)pixelBlue);
                    
                }
                else{
                    /*Blocked - Ambient only*/
                    pixelRed = AMBIENT_RED * AMBIENT_K * spheres[frontSphereIndex].r;
                    pixelGreen = AMBIENT_GREEN * AMBIENT_K * spheres[frontSphereIndex].g;
                    pixelBlue = AMBIENT_BLUE * AMBIENT_K * spheres[frontSphereIndex].b;
                    
                    setPixelColour(i, j, (GLfloat)pixelRed, (GLfloat)pixelGreen, (GLfloat)pixelBlue);
                }
                
            }
        }
    }
    
}


void printVector(Dim3Vector vector){
    printf("[%.2Lf, %.2Lf, %.2Lf]\n", vector.x, vector.y, vector.z);
}

void normalize(Dim3Vector * vector){
    long double vectorLength = sqrt(pow(vector->x, 2) + pow(vector->y, 2) + pow(vector->z, 2));
    
    vector->x = vector->x / vectorLength;
    vector->y = vector->y / vectorLength;
    vector->z = vector->z / vectorLength;
}

long double findLength(Dim3Vector origin, Dim3Vector destination){
    return sqrt(pow(destination.x - origin.x, 2) + pow(destination.y - origin.y, 2) + pow(destination.z - origin.z, 2));
}

long double dotProduct(Dim3Vector vec1, Dim3Vector vec2){
    return((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

/*Returns 1 if the angle between two vectors > 90 degrees, 0 otherwise*/
int isOppositeFromPoint(Dim3Vector center, Dim3Vector point1, Dim3Vector point2){
    Dim3Vector centerP1vec;
    Dim3Vector centerP2vec;

    centerP1vec.x = point1.x - center.x;
    centerP1vec.y = point1.y - center.y;
    centerP1vec.z = point1.z - center.z;
    normalize(&centerP1vec);
    
    centerP2vec.x = point2.x - center.x;
    centerP2vec.y = point2.y - center.y;
    centerP2vec.z = point2.z - center.z;
    normalize(&centerP2vec);
       
    if(dotProduct(centerP1vec, centerP2vec) <= 0){
        return 1;
    }
    else{
        return 0;
    }
}


int findDiscriminantSign(long double a, long double b, long double c){
    /*B^2 - 4AC*/
    long double discriminant = pow(b, 2) - (4 * a * c);
    
    if(discriminant > 0.00001){
        return 1;
    }
    else if(discriminant < 0.00001){
        return - 1;
    }
    else{
        return 0;
    }
}

/*Determine which sphere is intersected first*/
int determineFirstIntersection(Dim3Vector origin, Dim3Vector direction){
    int i;
    int closestSphereIndex = -1;
    long double closestSphereLength = -1;
    long double currentSphereLength = 0;
    
    Dim3Vector currentIntersection;
    
    for(i = 0; i < numberOfSpheres; i++){
        currentIntersection = determineIntersection(origin, direction, i);
        
        /*If there is no intersection, ignore it*/
        if(!((currentIntersection.x == VECX_NULL) && (currentIntersection.y == VECY_NULL) && (currentIntersection.z == VECZ_NULL))){
            if(closestSphereIndex == -1){
                closestSphereIndex = i;
                closestSphereLength = findLength(origin, currentIntersection);
            }
            else{
                currentSphereLength = findLength(origin, currentIntersection);
                if(currentSphereLength < closestSphereLength){
                    closestSphereIndex = i;
                    closestSphereLength = currentSphereLength;
                }
            }
        }
    }

    return closestSphereIndex;
}

/*Determine if the ray will reach the light.
  Return 0 if not blocked, return 1 if blocked*/
int isLightBlocked(Dim3Vector origin, Dim3Vector direction, int sphereSource){
    int i;
    long double currentSphereLength = 0;
    long double lightVecLength = findLength(origin, lightSource.pos);
    Dim3Vector currentIntersection;
    
    for(i = 0; i < numberOfSpheres; i++){
        /*Different check for a ray bouncing off a sphere intersecting that sphere*/
        if(i == sphereSource){
            currentIntersection = determineSelfIntersection(origin, direction, i);
        }
        else if(i != sphereSource){
            currentIntersection = determineIntersection(origin, direction, i);
        }
        
        /*If there is no intersection, or it only intersects the point the light ray started from, ignore it*/
        if(!((currentIntersection.x == VECX_NULL) && (currentIntersection.y == VECY_NULL) && (currentIntersection.z == VECZ_NULL))){
            currentSphereLength = findLength(origin, currentIntersection);
            if(currentSphereLength < lightVecLength){
                return 1;
            }
        }
    }
    
    return 0;
}

/*Returns the vector from the origin to the first intersection, and [-99999999, -99999999, -99999999] vector if no intersection*/
Dim3Vector determineIntersection(Dim3Vector origin, Dim3Vector direction, int sphereIndex){
    /*Components of the quadratic equation for the ray-sphere intersection*/
    long double quadraticA;
    long double quadraticB;
    long double quadraticC;
    int discriminantSign;
    long double quadraticT1;
    long double quadraticT2;
    
    long double vectorLength1;
    long double vectorLength2;
    
    /*Interesection positions*/
    Dim3Vector intersection1;
    Dim3Vector intersection2;
    
    normalize(&direction);
    
    Dim3Vector nullVector;
    nullVector.x = VECX_NULL;
    nullVector.y = VECY_NULL;
    nullVector.z = VECZ_NULL;
    
    quadraticA = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
    
    /*B = 2 * (Xd * (Xo - Xc) + Yd * (Yo - Yc) + Zd * (Zo - Zc))*/
    quadraticB = 2 * (direction.x * (origin.x - spheres[sphereIndex].pos.x)
                      + direction.y * (origin.y - spheres[sphereIndex].pos.y)
                      + direction.z * (origin.z - spheres[sphereIndex].pos.z));
    
    /*C = (Xo - Xc)^2 + (Yo - Yc)^2 + (Zo - Zc)^2 - Sr^2*/
    quadraticC = pow(origin.x - spheres[sphereIndex].pos.x, 2)
    + pow(origin.y - spheres[sphereIndex].pos.y, 2)
    + pow(origin.z - spheres[sphereIndex].pos.z, 2)
    - pow(spheres[sphereIndex].radius, 2);
    
    discriminantSign = findDiscriminantSign(quadraticA, quadraticB, quadraticC);
    
    switch(discriminantSign){
        case -1:
            /*No intersection, do nothing*/
            return nullVector;
        case 0:
            /*One intersection, one value for t, one normal*/
            quadraticT1 = -quadraticB / (2 * quadraticA);
            intersection1.x = origin.x + (direction.x * quadraticT1);
            intersection1.y = origin.y + (direction.y * quadraticT1);
            intersection1.z = origin.z + (direction.z * quadraticT1);

            if(isOppositeFromPoint(origin, intersection1, direction) == 1){
                return nullVector;
            }
            else{
                return(intersection1);
            }
        case 1:
            /*Two intersections, two values for t, two normals*/
            quadraticT1 = (-quadraticB - sqrt(pow(quadraticB, 2) - (4 * quadraticA * quadraticC))) / (2 * quadraticA);
            quadraticT2 = (-quadraticB + sqrt(pow(quadraticB, 2) - (4 * quadraticA * quadraticC))) / (2 * quadraticA);
            
            intersection1.x = origin.x + (direction.x * quadraticT1);
            intersection1.y = origin.y + (direction.y * quadraticT1);
            intersection1.z = origin.z + (direction.z * quadraticT1);
            
            intersection2.x = origin.x + (direction.x * quadraticT2);
            intersection2.y = origin.y + (direction.y * quadraticT2);
            intersection2.z = origin.z + (direction.z * quadraticT2);
            
            vectorLength1 = findLength(origin, intersection1);
            vectorLength2 = findLength(origin, intersection2);
            
            if(isOppositeFromPoint(origin, intersection1, direction) == 1){
                return nullVector;
            }
            else{
                if(vectorLength1 <= vectorLength2){
                    return(intersection1);
                }
                else{
                    return(intersection2);
                }
            }
        default:
            return nullVector;
    }
}


/*Returns the vector from the origin to the second intersection, and [-99999999, -99999999, -99999999] vector if 
  one or no intersections*/
Dim3Vector determineSelfIntersection(Dim3Vector origin, Dim3Vector direction, int sphereIndex){
    /*Components of the quadratic equation for the ray-sphere intersection*/
    long double quadraticA;
    long double quadraticB;
    long double quadraticC;
    int discriminantSign;
    long double quadraticT1;
    long double quadraticT2;
    
    long double vectorLength1;
    long double vectorLength2;
    
    /*Interesection positions*/
    Dim3Vector intersection1;
    Dim3Vector intersection2;
    
    Dim3Vector test1;
    Dim3Vector test2;
    
    normalize(&direction);
    
    Dim3Vector nullVector;
    nullVector.x = VECX_NULL;
    nullVector.y = VECY_NULL;
    nullVector.z = VECZ_NULL;

    quadraticA = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
    
    /*B = 2 * (Xd * (Xo - Xc) + Yd * (Yo - Yc) + Zd * (Zo - Zc))*/
    quadraticB = 2 * (direction.x * (origin.x - spheres[sphereIndex].pos.x)
                      + direction.y * (origin.y - spheres[sphereIndex].pos.y)
                      + direction.z * (origin.z - spheres[sphereIndex].pos.z));
    
    /*C = (Xo - Xc)^2 + (Yo - Yc)^2 + (Zo - Zc)^2 - Sr^2*/
    quadraticC = pow(origin.x - spheres[sphereIndex].pos.x, 2)
    + pow(origin.y - spheres[sphereIndex].pos.y, 2)
    + pow(origin.z - spheres[sphereIndex].pos.z, 2)
    - pow(spheres[sphereIndex].radius, 2);
    
    discriminantSign = findDiscriminantSign(quadraticA, quadraticB, quadraticC);
    
    switch(discriminantSign){
        case -1:
            /*No intersection, do nothing*/
            return nullVector;
        case 0:
            /*One intersection, check if its not the trivial intersection*/
            quadraticT1 = (-quadraticB - sqrt(pow(quadraticB, 2) - (4 * quadraticA * quadraticC))) / (2 * quadraticA);
            
            intersection1.x = origin.x + (direction.x * quadraticT1);
            intersection1.y = origin.y + (direction.y * quadraticT1);
            intersection1.z = origin.z + (direction.z * quadraticT1);
            
            vectorLength1 = findLength(origin, intersection1);
            
            if(vectorLength1 < 0.00001){
                return nullVector;
            }
            return intersection1;
        case 1:
            /*Two intersections, two values for t, two normals*/
            quadraticT1 = (-quadraticB - sqrt(pow(quadraticB, 2) - (4 * quadraticA * quadraticC))) / (2 * quadraticA);
            quadraticT2 = (-quadraticB + sqrt(pow(quadraticB, 2) - (4 * quadraticA * quadraticC))) / (2 * quadraticA);
            
            intersection1.x = origin.x + (direction.x * quadraticT1);
            intersection1.y = origin.y + (direction.y * quadraticT1);
            intersection1.z = origin.z + (direction.z * quadraticT1);
            
            intersection2.x = origin.x + (direction.x * quadraticT2);
            intersection2.y = origin.y + (direction.y * quadraticT2);
            intersection2.z = origin.z + (direction.z * quadraticT2);
            
            vectorLength1 = findLength(origin, intersection1);
            vectorLength2 = findLength(origin, intersection2);
            
            
            if((vectorLength1 < 0.00001) && (vectorLength2 < 0.00001)){
                return nullVector;
            }
            
            if(vectorLength1 >= vectorLength2){
                if(isOppositeFromPoint(origin, intersection1, direction) == 1){
                    return nullVector;
                }
                else{
                    return(intersection1);
                }
            }
            else{
                if(isOppositeFromPoint(origin, intersection2, direction) == 1){
                    /*Equal/not equal buggy*/
                    return nullVector;
                }
                else{
                    return(intersection2);
                }
            }
        default:
            return nullVector;
    }
}

