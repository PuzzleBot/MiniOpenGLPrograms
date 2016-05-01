#include "a2.h"

double cameraAngle = 180.0;
double cameraZoom = 0.0;

void transformCamera(double degrees, double zoomDist){
    /* Set the rotation angle for the whole scene */
    cameraAngle = cameraAngle + degrees;

    /*To prevent overflow, keep the angle between -360 and 360*/
    if(cameraAngle > 360){
        cameraAngle = fmod(cameraAngle, 360);
    }
    
    if(cameraAngle < -360){
        cameraAngle = fmod(cameraAngle, 360);
    }
    
    /* Set the zoom amount for the whole screen */
    cameraZoom = cameraZoom - (zoomDist / 4);
    
    /*Do not allow zooming in through the object*/
    if(cameraZoom > (DISPLAYHEIGHT/2)){
        cameraZoom = DISPLAYHEIGHT/2;
    }
}