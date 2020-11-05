//
// Created by tim on 11/4/20.
//

#ifndef SPACE_ACE_PROJECTILE_H
#define SPACE_ACE_PROJECTILE_H

#include "graphic.h"
#include "collisionmath.h"
#include <ultra64.h>

#define MAX_PROJECTILES 200
#define DEFAULT_DISTANCE 3
#define DEFAULT_RADIUS 3
#define MAX_TRAVEL_DISTANCE 3000
#define PROJECTILE_SPEED 400;

typedef struct Projectile{
    Vec3d forward;
    Vec3d pos;
    Vec3d initial_pos;
    float speed;
    Mtx transform;
    float radius;
    int isEliminated;
} Projectile;

//Fast acos approximation
float effabs(float x){
    return sqrtf(x * x);
}

float effacos(float x) {
    float negate = (float)(x < 0);
    x = effabs(x);
    float ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * sqrtf(1.0-x);
    ret = ret - 2 * negate * ret;
    return negate * 3.14159265358979 + ret;
}


Projectile instantiate_projectile(Vec3d playerPos, Vec3d playerForward, float distance, float radius) {
    long identity[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
    float playerMagnitude = sqrtf(playerPos.x * playerPos.x + playerPos.y * playerPos.y + playerPos.z * playerPos.z);

    Vec3d playerPosNorm = {
            playerPos.x / playerMagnitude,
            playerPos.y / playerMagnitude,
            playerPos.z / playerMagnitude
    };

    Vec3d startPos = {
            playerPos.x + playerPosNorm.x * distance,
            playerPos.y + playerPosNorm.y * distance,
            playerPos.z + playerPosNorm.z * distance
    };

    Projectile projOut;

    projOut.forward = playerForward;
    projOut.pos = startPos;
    projOut.radius = radius;
    projOut.initial_pos = projOut.pos;
    projOut.isEliminated = 0;
    projOut.speed = PROJECTILE_SPEED;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            projOut.transform.m[i][j] = identity[i][j];
        }
    }
    return projOut;
}

void initialize_projectile_array(Projectile * array){
    for(int i = 0; i < MAX_PROJECTILES; i++){
        array[i].isEliminated = 1;
    }
}

void fire_projectile(Vec3d playerPos, Vec3d playerForward, Projectile * array, int * projectile_count){
    if(*projectile_count < MAX_PROJECTILES){
        *projectile_count = *projectile_count + 1;

        int i = 0;

        while(!array[i].isEliminated){
            i++;
        }

        array[i] = instantiate_projectile(playerPos, playerForward, DEFAULT_DISTANCE, DEFAULT_RADIUS);
    }
}

void cull_projectiles(Projectile * array){
    for(int i = 0; i < MAX_PROJECTILES; i++){
        if(!array[i].isEliminated){
            Vec3d pos = array[i].pos;
            Vec3d init_pos = array[i].initial_pos;

            Vec3d diff = {
                    pos.x - init_pos.x,
                    pos.y - init_pos.y,
                    pos.z - init_pos.z,
            };

            float distance_travelled = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

            if(distance_travelled > MAX_TRAVEL_DISTANCE){
                array[i].isEliminated = 1;
            }
        }
    }
}

void rotate_to_player(Projectile * projectile, Vec3d playerForward){
    Vec3d axis;
    float angle;
    Mtx rotation_matrix;

    Vec3d projectileForward = projectile->forward;
    Vec3d crossProduct ={
            projectileForward.y * playerForward.z - projectileForward.z * playerForward.y,
            projectileForward.z * playerForward.x - projectileForward.x * playerForward.z,
            projectileForward.x * playerForward.y - projectileForward.y * playerForward.x
    };

    float crossMag = sqrtf(crossProduct.x * crossProduct.x + crossProduct.y * crossProduct.y +
            crossProduct.z * crossProduct.z);

    float projMag = sqrtf(projectileForward.x * projectileForward.x + projectileForward.y * projectileForward.y
            + projectileForward.z * projectileForward.z);
    float playerMag = sqrtf(playerForward.x * playerForward.x + playerForward.y * playerForward.y
            + playerForward.z * playerForward.z);

    float dotProd = projectileForward.x * playerForward.x + projectileForward.y * playerForward.y +
            projectileForward.z * playerForward.z;

    if(projMag != 0){
        axis.x = crossProduct.x / crossMag;
        axis.y = crossProduct.x / crossMag;
        axis.z = crossProduct.x / crossMag;

        angle = effacos(dotProd / (projMag * playerMag));

        guRotate(&rotation_matrix, angle, axis.x, axis.y, axis.z);

        //Rotate the forward vector
        guMtxXFML(&rotation_matrix, projectile->forward.x, projectile->forward.y, projectile->forward.z,
                  &(projectile->forward.x), &(projectile->forward.y), &(projectile->forward.z));

        //Rotate the object itself
        guMtxCatL(&rotation_matrix, &(projectile->transform), &(projectile->transform));

    }


}

void move_projectiles(Projectile * projectiles){

}

#endif //SPACE_ACE_PROJECTILE_H
