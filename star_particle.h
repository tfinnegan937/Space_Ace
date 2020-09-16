//
// Created by Tim on 9/9/2020.
//

#ifndef SPACE_ACE_STAR_PARTICLE_H
#define SPACE_ACE_STAR_PARTICLE_H
#include <ultra64.h>
#include <nusys.h>
#include "graphic.h"

#define MAX_STAR_PARTICLES 50
#define STAR_PARTICLE_RENDER_DISTANCE 100

typedef struct StarParticle{
    Vec3d position;
    float scale_factor;
    unsigned short marked_for_deletion;
}StarParticle;

extern StarParticle particle_list[MAX_STAR_PARTICLES];

extern int star_particle_count;

extern float translation_matrix[4][4];

extern float rotation_matrix[4][4];

typedef struct ProjectionOutput{
    float x;
    float y;
    float z;
} ProjectionOutput;

extern Vec3d axisOfRotation;

extern float angleOfRotation;
extern struct StarParticle newParticle;
extern void drawStarParticle(StarParticle);
extern void generateStarParticle(Vec3d);
extern void cullStarParticles(Vec3d);
extern void updateStarParticles(Vec3d, Vec3d);
extern float fastacos(float);
#endif //SPACE_ACE_STAR_PARTICLE_H
