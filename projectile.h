//
// Created by tim on 11/4/20.
//

#ifndef SPACE_ACE_PROJECTILE_H
#define SPACE_ACE_PROJECTILE_H


#define MAX_PROJECTILES 200
#define DEFAULT_DISTANCE 10
#define DEFAULT_RADIUS 3
#define MAX_TRAVEL_DISTANCE 3000
#define PROJECTILE_SPEED 250;

#include "graphic.h"
#include <ultra64.h>
#include "debug.h"


typedef struct Projectile{
    Vec3d forward;
    Vec3d look_forward;
    Vec3d pos;
    Vec3d initial_pos;
    float speed;
    Mtx transform;
    Mtx translation;
    float radius;
    int isEliminated;
} Projectile;

//Fast acos approximation
float effabs(float x);

float effacos(float x);


Projectile instantiate_projectile(Vec3d playerPos, Vec3d playerForward, float distance, float radius);

void initialize_projectile_array(Projectile * array);

void fire_projectile(Vec3d playerPos, Vec3d playerForward, Projectile * array, int * projectile_count);

void cull_projectiles(Projectile * array, int * projectile_count);

void rotate_proj_to_player(Projectile * projectile, Vec3d playerForward);

void move_projectiles(Projectile * projectiles);

void handle_projectiles(Projectile * projectiles, Vec3d playerForward, Vec3d playerPos, int * projectile_count);


#endif //SPACE_ACE_PROJECTILE_H
