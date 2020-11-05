
#include <assert.h>
#include <nusys.h>
#include <ultra64.h>
#include "graphic.h"
#include "main.h"
#include "stage00.h"
#include "skybox.h"
#include "cube_render.h"
#include "debug.h"
#include "testcube.h"
#include "meteor.h"
#include "collisionmath.h"
#include "projectile_texture.h"
#include "projectile.h"

Vec3d cameraPos = {0.0f, 0.0f, -50.0f};
Vec3d cameraTarget = {0, 0, 0};
Vec3d cameraForward = {0.0f, 0.0f, 1.0f};
Vec3d cameraEulerAngles = {0.0f, 0.0f, 0.0f};
Vec3d cameraUp = {0.0f, 1.0f, 0.0f};
Vec3d cameraLeft = {1.0f, 0.0f, 0.0f};

//booleans
char pitch = 0;
char roll = 0;
char yaw = 0;

char skyboxOn = 1;

char yawDirection = 1;
char rollDirection = 1;
char pitchDirection = 1;

float yawVelocity = 127;
float pitchVelocity = 127;
float rollVelocity = 127;

float forwardVelocity = 0;
float forwardMin = -200;
float forwardMax = 500;

Vec3d playerVelocity = {
        0,
        0,
        0
};

float forwardAcceleration = 500;

Mtx skyboxTranslation;

float yawRotation[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
};

float pitchRotation[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
};

float rollRotation[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
};

Mtx curMeteorRotation;

Mtx curMeteorTranslation;

#define METEOR_COUNT 100
struct Meteor MeteorList[METEOR_COUNT];

Mtx MeteorTransformationStack[METEOR_COUNT];

int test_rotations[METEOR_COUNT];

Vec3d test_positions[METEOR_COUNT];

Projectile projectiles[MAX_PROJECTILES];

// the 'setup' function
void initStage00() {  
  // the advantage of initializing these values here, rather than statically, is
  // that if you switch stages/levels, and later return to this stage, you can
  // call this function to reset these values.


  // In the older version of C used by the N64 compiler (roughly C89); variables
  // must be declared at the top of a function or block scope. This is an example
  // of using block scope to declare a variable in the middle of a function.
  generateMeteors();
  initialize_projectile_array(projectiles);

}

// the 'update' function
void updateGame00() {
  // read controller input from controller 1 (index 0)
  nuContDataGetEx(contdata, 0);


  float joystickMagnitude = sqrtf(contdata[0].stick_y * contdata[0].stick_y + contdata[0].stick_x * contdata[0].stick_x);

  if (contdata[0].button & A_BUTTON){
    //forwardVelocity = forwardVelocity + forwardAcceleration;
      playerVelocity.x += cameraForward.x * forwardAcceleration *.016;
      playerVelocity.y += cameraForward.y * forwardAcceleration *.016;
      playerVelocity.z += cameraForward.z * forwardAcceleration *.016;
      //playerVelocity = applyInertDamp(cameraForward, playerVelocity, 75, 1);

  }



  if (contdata[0].button & B_BUTTON){
    //forwardVelocity = forwardVelocity - forwardAcceleration;
    playerVelocity.x += -1 * cameraForward.x * forwardAcceleration * .016;
    playerVelocity.y += -1 * cameraForward.y * forwardAcceleration * .016;
    playerVelocity.z += -1 * cameraForward.z * forwardAcceleration * .016;
    //playerVelocity = applyInertDamp(cameraForward, playerVelocity, 75, -1);

  }

  float velocityMagnitude = sqrtf(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y
                              + playerVelocity.z * playerVelocity.z);

  if(velocityMagnitude > forwardMax){
      Vec3d normalizedVelocity = {
              playerVelocity.x / velocityMagnitude,
              playerVelocity.y / velocityMagnitude,
              playerVelocity.z / velocityMagnitude
      };

      playerVelocity.x = normalizedVelocity.x * forwardMax;
      playerVelocity.y = normalizedVelocity.y * forwardMax;
      playerVelocity.z = normalizedVelocity.z * forwardMax;
  }


  if(contdata[0].button & U_CBUTTONS){
      playerVelocity.x = 0;
      playerVelocity.y = 0;
      playerVelocity.z = 0;
  }
  roll = 0;
  if (contdata[0].button & L_CBUTTONS){
    roll = 1;
    rollDirection = -1;
  }

  if (contdata[0].button & R_CBUTTONS){
    roll = 1;
    rollDirection = 1;
  }
    if(contdata[0].trigger & D_CBUTTONS){
        skyboxOn = skyboxOn * -1;
    }
  yaw = 0;

  int stick_x_mag = sqrtf(contdata[0].stick_x * contdata[0].stick_x);
  int stick_y_mag = sqrtf(contdata[0].stick_y * contdata[0].stick_y);
  if(contdata[0].stick_x !=0 && (stick_x_mag > 40)){
      //debug_printf("x: %x\n", contdata[0].stick_x);
      yaw = 1;
      yawDirection = contdata[0].stick_x / sqrtf(contdata[0].stick_x * contdata[0].stick_x);
  }
  pitch = 0;
  if(contdata[0].stick_y !=0 && (stick_y_mag > 40)){
    pitch = 1;
      //debug_printf("y: %x\n", contdata[0].stick_y);

      pitchDirection = contdata[0].stick_y / sqrtf(contdata[0].stick_y * contdata[0].stick_y);
  }

  // update square rotations


  cameraPos.x = cameraPos.x + (playerVelocity.x * .016);
  cameraPos.y = cameraPos.y + (playerVelocity.y * .016);
  cameraPos.z = cameraPos.z + (playerVelocity.z * .016);

  //Detect collisions

  for(int i = 0; i < METEOR_COUNT; i++){
      float meteorRadius = MeteorList[i].radius * MeteorList[i].scale;
      Vec3d meteorPosition = MeteorList[i].position;
      if(isColliding(50, meteorRadius, cameraPos, MeteorList[i].position)){
          VelocityOut collisionOutput;
          Vec3d oppositeVelocity = {
                  -1 * playerVelocity.x,
                  -1 * playerVelocity.y,
                  -1 * playerVelocity.z
          };
          collisionOutput = respondCollision(50, cameraPos, playerVelocity, 770, meteorRadius, meteorPosition,
                                             oppositeVelocity, 5000);

          playerVelocity = collisionOutput.first;
      }
  }

  cameraTarget.x = cameraPos.x + cameraForward.x;
  cameraTarget.y = cameraPos.y + cameraForward.y;
  cameraTarget.z = cameraPos.z + cameraForward.z;

  updateMeteors();

  //debug_printf("Velocity: %f %f %f \n", playerVelocity.x, playerVelocity.y, playerVelocity.z);
  //debug_printf("Magnitude: %f Forward Max: %f\n", velocityMagnitude, forwardMax);

  //debug_printf("Position: %f %f %f \n", cameraPos.x, cameraPos.y, cameraPos.z);
}

// the 'draw' function
void makeDL00() {
  unsigned short perspNorm;
  GraphicsTask * gfxTask;

  // switch the current graphics task
  // also updates the displayListPtr global variable
  gfxTask = gfxSwitchTask(); 


  // prepare the RCP for rendering a graphics task
  gfxRCPInit();

  // clear the color framebuffer and Z-buffer, similar to glClear()
  gfxClearCfb();
  //gfxSetBackgroundColor();


    //debug_printf("Rom initialized");

    //Perform the camera vector rotations
  if(yaw) {
      guRotateF(yawRotation, -1 * yawVelocity * yawDirection * .016, cameraUp.x, cameraUp.y, cameraUp.z);
      guMtxXFMF(yawRotation, cameraForward.x, cameraForward.y, cameraForward.z,
                  &cameraForward.x, &cameraForward.y, & cameraForward.z);
      guMtxXFMF(yawRotation, cameraLeft.x, cameraLeft.y, cameraLeft.z,
                  &cameraLeft.x, &cameraLeft.y, &cameraLeft.z);
  }
  if(pitch) {
      guRotateF(pitchRotation, -1 * pitchVelocity * pitchDirection * .016, cameraLeft.x, cameraLeft.y, cameraLeft.z);
      guMtxXFMF(pitchRotation, cameraForward.x, cameraForward.y, cameraForward.z,
                &cameraForward.x, &cameraForward.y, & cameraForward.z);
      guMtxXFMF(pitchRotation, cameraUp.x, cameraUp.y, cameraUp.z,
                &cameraUp.x, &cameraUp.y, &cameraUp.z);
  }
  if(roll) {
      guRotateF(rollRotation, -1 * rollVelocity * rollDirection * .016, cameraForward.x, cameraForward.y, cameraForward.z);
      guMtxXFMF(rollRotation, cameraLeft.x, cameraLeft.y, cameraLeft.z,
                &cameraLeft.x, &cameraLeft.y, & cameraLeft.z);
      guMtxXFMF(rollRotation, cameraUp.x, cameraUp.y, cameraUp.z,
                &cameraUp.x, &cameraUp.y, &cameraUp.z);
  }

  guNormalize(&cameraForward.x, &cameraForward.y, &cameraForward.z);
  // initialize the projection matrix, similar to glPerspective() or glm::perspective()
  guPerspective(&gfxTask->projection, &perspNorm, FOVY, ASPECT, NEAR_PLANE,
                FAR_PLANE, 1.0);

  // Our first actual displaylist command. This writes the command as a value at
  // the tail of the current display list, and we increment the display list
  // tail pointer, ready for the next command to be written.
  // As for what this command does... it's just required when using a perspective
  // projection. Try pasting 'gSPPerspNormalize' into google if you want more
  // explanation, as all the SDK documentation has been placed online by
  // hobbyists and is well indexed.
  gSPPerspNormalize(displayListPtr++, perspNorm);

  // initialize the modelview matrix, similar to gluLookAt() or glm::lookAt()
  guLookAt(&gfxTask->modelview, cameraPos.x, cameraPos.y,
           cameraPos.z, cameraTarget.x, cameraTarget.y,
           cameraTarget.z, cameraUp.x, cameraUp.y, cameraUp.z);



  // load the projection matrix into the matrix stack.
  // given the combination of G_MTX_flags we provide, effectively this means
  // "replace the projection matrix with this new matrix"
  gSPMatrix(
    displayListPtr++,
    // we use the OS_K0_TO_PHYSICAL macro to convert the pointer to this matrix
    // into a 'physical' address as required by the RCP 
    OS_K0_TO_PHYSICAL(&(gfxTask->projection)),
    // these flags tell the graphics microcode what to do with this matrix
    // documented here: http://n64devkit.square7.ch/tutorial/graphics/1/1_3.htm
    G_MTX_PROJECTION | // using the projection matrix stack...
    G_MTX_LOAD | // don't multiply matrix by previously-top matrix in stack
    G_MTX_NOPUSH // don't push another matrix onto the stack before operation
  );

  gSPMatrix(displayListPtr++,
    OS_K0_TO_PHYSICAL(&(gfxTask->modelview)),
    // similarly this combination means "replace the modelview matrix with this new matrix"
    G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_LOAD
  );

    guTranslate(&skyboxTranslation, cameraPos.x, cameraPos.y, cameraPos.z);
    gSPMatrix(displayListPtr++, &skyboxTranslation, G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);
    if(skyboxOn > -1) {
        gSPDisplayList(displayListPtr++, skybox_dl);
    }
    gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);

    gSPDisplayList(displayListPtr++, projectile_dl);

    drawMeteors();

    gDPPipeSync(displayListPtr++);
    //debug_printf("%i FPS\n", nuScGetFrameRate());


    // mark the end of the display list
  gDPFullSync(displayListPtr++);
  gSPEndDisplayList(displayListPtr++);

  //draw the star particles;
  //TODO draw the star particles

  //This is commented out as it causes an emulator crash
  //TODO fix star particle drawing
  //updateStarParticles(cameraPos, cameraForward);


  // assert that the display list isn't longer than the memory allocated for it,
  // otherwise we would have corrupted memory when writing it.
  // isn't unsafe memory access fun?
  // this could be made safer by instead asserting on the displaylist length
  // every time the pointer is advanced, but that would add some overhead.
  assert(displayListPtr - gfxTask->displayList < MAX_DISPLAY_LIST_COMMANDS);

  // create a graphics task to render this displaylist and send it to the RCP
  nuGfxTaskStart(
    gfxTask->displayList,
    (int)(displayListPtr - gfxTask->displayList) * sizeof (Gfx),
    NU_GFX_UCODE_F3DEX2, // load the 'F3DEX' version graphics microcode, which runs on the RCP to process this display list
    NU_SC_SWAPBUFFER // tells NuSystem to immediately display the frame on screen after the RCP finishes rendering it
  );
}

// the nusystem callback for the stage, called once per frame
void stage00(int pendingGfx)
{
  // produce a new displaylist (unless we're running behind, meaning we already
  // have the maximum queued up)
  if(pendingGfx < 1)
    makeDL00();

  // update the state of the world for the next frame
  updateGame00();
}



void generateMeteors(){
    //Generate values for each meteor.
    for(int i = 0; i < METEOR_COUNT; i++){
        MeteorList[i].position.x = RAND(6000) - 3000;
        MeteorList[i].position.y = RAND(6000) - 3000;
        MeteorList[i].position.z = RAND(6000) - 3000;

        MeteorList[i].Turning_Axis.x = RAND(2) - 1; //Range 1 - 101 inclusive, shifted to 0 - 100, normalized
        MeteorList[i].Turning_Axis.y = RAND(2) - 1;
        MeteorList[i].Turning_Axis.z = RAND(2) - 1;

        MeteorList[i].rotation_angle = 13;
        MeteorList[i].scale = RAND(3);
        MeteorList[i].radius = 215;
        //debug_printf("Angle of rotation: %i\n", test_rotations[i]);
        //debug_printf("X: %f\n", test_positions[i].x);


    }
}

void updateMeteors(){
    for(int i = 0; i < METEOR_COUNT; i++){
        MeteorList[i].rotation_angle = ((MeteorList[i].rotation_angle + 1) % 360); //Rotate the meteors.
    }
}



void drawMeteors(){

    gSPDisplayList(displayListPtr++, asteroid_material);
    for(int i = 0; i < METEOR_COUNT; i++){

        struct Meteor curMeteor = MeteorList[i];



        //debug_printf("X: %f Y: %f Z %f \n", curMeteor.x, curMeteor.y, curMeteor.z);
        //debug_printf("Angle of rotation: %f\n", curMeteor.rotation_angle);

        int rotation_x = curMeteor.Turning_Axis.x * curMeteor.rotation_angle;
        int rotation_y = curMeteor.Turning_Axis.y * curMeteor.rotation_angle;
        int rotation_z = curMeteor.Turning_Axis.z * curMeteor.rotation_angle;

        guPosition(&MeteorTransformationStack[i], rotation_x, rotation_y, rotation_z, curMeteor.scale,
                   curMeteor.position.x, curMeteor.position.y, curMeteor.position.z);
        gSPMatrix(displayListPtr++, OS_K0_TO_PHYSICAL(&MeteorTransformationStack[i]), G_MTX_MODELVIEW | G_MTX_PUSH);
        gSPDisplayList(displayListPtr++, asteroid_Sphere_mesh);

        gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);

    }
}

Vec3d applyInertDamp(Vec3d forward, Vec3d velocity, float rate, int forwardScale){

    float velMag = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);

    if(velMag == 0){
        velMag = 1;
    }

    //Scale the forward vector by the current velocity magnitude
    Vec3d desiredVelocity = {
        forwardScale * forward.x * velMag,
        forwardScale * forward.y * velMag,
        forwardScale * forward.z * velMag
    };

    //Take the difference between the two vectors
    Vec3d difference = {
            velocity.x - desiredVelocity.x,
            velocity.y - desiredVelocity.y,
            velocity.z - desiredVelocity.z
    };

    //normalize the difference then scale it by the rate
    float difMag = sqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);

    if(difMag == 0){
        difMag = 1;
    }

    Vec3d change = {
            (difference.x / difMag) * rate * .016,
            (difference.y / difMag) * rate * .016,
            (difference.z / difMag) * rate * .016
    };

    //update the input velocity
    Vec3d output = {
            velocity.x + change.x,
            velocity.y + change.y,
            velocity.z + change.z
    };

    return output;
}
