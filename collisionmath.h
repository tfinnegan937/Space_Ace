//
// Created by tim on 10/14/20.
//

#ifndef SPACE_ACE_COLLISIONMATH_H
#define SPACE_ACE_COLLISIONMATH_H
#include <ultra64.h>
#include "graphic.h"

extern int isColliding(float radius1, float radius2, Vec3d pos1, Vec3d pos2);

int isColliding(float radius1, float radius2, Vec3d pos1, Vec3d pos2){
    Vec3d difference;
    difference.x = pos2.x - pos1.x;
    difference.y = pos2.y - pos1.y;
    difference.z = pos2.z - pos1.z;

    float distance = sqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);

    float radSum = radius1 + radius2;

    if(distance < radSum){
        return 1;
    }

    return 0;
}

typedef struct VelocityOut {
    Vec3d first;
    Vec3d second;
} VelocityOut;


//WORK IN PROGRESS. DO NOT USE
VelocityOut respondCollision(float playerRad, Vec3d playerPos, Vec3d playerVel, float playerMass,
                     float objectRad, Vec3d objectPos, Vec3d objectVel, float objectMass){
    //Create the basis
    Vec3d xBasis = {
            objectPos.x - playerPos.x,
            objectPos.y - playerPos.y,
            objectPos.z - playerPos.z
    };

    //Normalize the basis
    float xBaseMag = sqrtf(xBasis.x * xBasis.x + xBasis.y * xBasis.y + xBasis.z * xBasis.z);

    xBasis.x = xBasis.x / xBaseMag;
    xBasis.y = xBasis.y / xBaseMag;
    xBasis.z = xBasis.z / xBaseMag;

    float x1 = playerVel.x * xBasis.x + playerVel.y * xBasis.y + playerVel.z * xBasis.z;

    Vec3d vecv1x = {
            x1 * xBasis.x,
            x1 * xBasis.y,
            x1 * xBasis.z
    };

    Vec3d vecv1y = {
            playerVel.x - vecv1x.x,
            playerVel.y - vecv1x.y,
            playerVel.z - vecv1x.z
    };

    xBasis.x = xBasis.x * -1;
    xBasis.y = xBasis.y * -1;
    xBasis.z = xBasis.z * -1;

    float x2 = objectVel.x * xBasis.x + objectVel.y * xBasis.y + objectVel.z * xBasis.z;

    Vec3d vecv2x = {
            x2 * xBasis.x,
            x2 * xBasis.y,
            x2 * xBasis.z
    };

    Vec3d vecv2y = {
            objectVel.x - vecv2x.x,
            objectVel.y - vecv2x.y,
            objectVel.z - vecv2x.z
    };

    float mass_difference = objectMass - playerMass;
    float mass_sum = objectMass + playerMass;

    Vec3d playerVelocity = {
        vecv1x.x * (mass_difference/mass_sum) + vecv2x.x * ((2 * playerMass) / mass_sum) + vecv1y.x,
        vecv1x.y * (mass_difference/mass_sum) + vecv2x.y * ((2 * playerMass) / mass_sum) + vecv1y.y,
        vecv1x.z * (mass_difference/mass_sum) + vecv2x.z * ((2 * playerMass) / mass_sum) + vecv1y.z,

    };

    Vec3d objectVelocity = {
            vecv1x.x * ((2 * playerMass) / mass_sum) + vecv2x.x * (mass_difference / mass_sum) + vecv2y.x,
            vecv1x.y * ((2 * playerMass) / mass_sum) + vecv2x.y * (mass_difference / mass_sum) + vecv2y.y,
            vecv1x.z * ((2 * playerMass) / mass_sum) + vecv2x.z * (mass_difference / mass_sum) + vecv2y.z

    };

    VelocityOut velocities = {
            playerVelocity,
            objectVelocity
    };

    return velocities;
}


#endif //SPACE_ACE_COLLISIONMATH_H
