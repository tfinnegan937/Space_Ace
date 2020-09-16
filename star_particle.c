//
// Created by Tim on 9/9/2020.
//
#include "star_particle.h"
#include <nusys.h>
#include <ultra64.h>
#include "graphic.h"
int star_particle_count = 0;

float translation_matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
};

float rotation_matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
};


Vec3d axisOfRotation = {
        0.0f,
        0.0f,
        0.0f
};

float angleOfRotation = 0;

float fastacos(float in) {
    float negate = (float)(in < 0);
    float x = in;
    if(in < 0){
        x = x * -1;
    }
    float ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * sqrtf(1.0-x);
    ret = ret - 2 * negate * ret;
    return (negate * 3.14159265358979 + ret) * 3.14159265358979; //Additional pi factor converts to degrees
}

void cullStarParticles(Vec3d cameraPos){
    struct StarParticle cursor = {
            {0, 0, 0},
            1,
            0
    };

    struct ProjectionOutput out = {
            0,
            0,
            0,
    };

    for(int i = 0; i < star_particle_count; i++){
        cursor = particle_list[i];
        //translate the point back to the origin (Such that their position within the box can be determined
        //A rotation should be added to this later
        guTranslateF(translation_matrix, -1 * cameraPos.x, -1 * cameraPos.y, -1 * cameraPos.z);

        guMtxXFMF(translation_matrix, cursor.position.x, cursor.position.y, cursor.position.z,
                  &out.x, &out.y, &out.z);
        //If the point is outside of the box, mark it for deletion.
        if(out.x > STAR_PARTICLE_RENDER_DISTANCE
        || out.y > STAR_PARTICLE_RENDER_DISTANCE
        || out.z > STAR_PARTICLE_RENDER_DISTANCE
        || out.x < -1 * STAR_PARTICLE_RENDER_DISTANCE
        || out.y < -1 * STAR_PARTICLE_RENDER_DISTANCE
        || out.z < -1 * STAR_PARTICLE_RENDER_DISTANCE){
            particle_list[i].marked_for_deletion = 1;
        }
    }

    for(int i = 0; i < star_particle_count; i++){
        //If the current particle is marked for deletion,
        if(particle_list[i].marked_for_deletion == 1){
            //Decrease the end index of the list until either:
            // -It finds a particle that is not marked for deletion
            // -It reaches the last index, meaning that all particles must be deleted
            // -The current particle is already the last particle in the list.
            while(
                    particle_list[(star_particle_count - 1)].marked_for_deletion == 1
                    && star_particle_count !=0
                    && star_particle_count - 1 != i
                    ){
                star_particle_count = star_particle_count - 1;
            }

            //swap the last element and the current element
            //If there is only one element left in the list, the list is deleted
            if(star_particle_count > 1) {
                StarParticle temp = particle_list[i];
                particle_list[i] = particle_list[star_particle_count - 1];
                particle_list[star_particle_count - 1] = temp;
            }
            //lower the end index by 1
            star_particle_count = star_particle_count - 1;
        }
    }


}

void generateStarParticle(Vec3d cameraPos){
    star_particle_count = star_particle_count + 1;
    struct StarParticle newParticle = {
            {0, 0, 0},
            1,
            0
    };

    newParticle.scale_factor = RAND(3) + 1; //scaled 1x, 2x, or 3x. RAND generates range 0, max - 1

    newParticle.marked_for_deletion = 0; //New particles should not be deleted

    //randomly assign the point to a space somewhere in the box.
    newParticle.position.x = (RAND(STAR_PARTICLE_RENDER_DISTANCE * 2) + 1) - STAR_PARTICLE_RENDER_DISTANCE;
    newParticle.position.y = (RAND(STAR_PARTICLE_RENDER_DISTANCE * 2) + 1) - STAR_PARTICLE_RENDER_DISTANCE;
    newParticle.position.z = (RAND(STAR_PARTICLE_RENDER_DISTANCE * 2) + 1) - STAR_PARTICLE_RENDER_DISTANCE;

    //Translate the point to its current spot in space
    guTranslateF(translation_matrix, cameraPos.x, cameraPos.y, cameraPos.z);
    //Apply the translation
    guMtxXFMF(translation_matrix, newParticle.position.x, newParticle.position.y, newParticle.position.z,
              &newParticle.position.x, &newParticle.position.y, &newParticle.position.z);
    //Add the particle to the list
    particle_list[star_particle_count - 1] = newParticle;

}

void drawStarParticle(StarParticle particle){
    //TODO Implement the vertlist and the displaylist for particles

}

void updateStarParticles(Vec3d cameraPos, Vec3d cameraForward){
    //Cull the current particle list
    cullStarParticles(cameraPos);
    //Generate particles until maximum number has been drawn
    while(star_particle_count < MAX_STAR_PARTICLES){
        generateStarParticle(cameraPos);
    }

    //Recover the axis of rotation for billboarding

    //forward vector for the particles is always (0, 0, 1)

    //| 0 1 |
    //| y 1 | i = (0 - y)
    axisOfRotation.x = -1 * cameraForward.y;

    //     | 0 1 |
    //-1 * | x z |j = -( 0 - x)j = xj

    axisOfRotation.y = -1 * cameraForward.x;

    // |0 0|
    // |x z|k = 0

    axisOfRotation.z = 0;

    //Recover the angle of rotation for billboarding

    //(x, y, z) dot (0, 0, 1) = 0 * x + 0 * y + 1 * z = z
    float cos_length = cameraForward.z * 1;

    //magnitude of (0, 0, 1) is 1

    cos_length = cos_length / sqrtf(cameraForward.x * cameraForward.x + cameraForward.y * cameraForward.y +
            cameraForward.z * cameraForward.z);

    angleOfRotation = fastacos(cos_length);

    //Generate rotation matrix, apply rotation matrix, and render each particle

    //TODO APPLY ROTATION MATRIX

    guRotateF(rotation_matrix, angleOfRotation, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);

    gSPMatrix(displayListPtr++, OS_K0_TO_PHYSICAL(&rotation_matrix), G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);

    for(int i = 0; i < star_particle_count; i++){
        drawStarParticle(particle_list[i]);
    }

    //TODO POP ROTATION MATRIX
    gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);
    gDPPipeSync(displayListPtr++);
}