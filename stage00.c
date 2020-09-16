
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
#include "ufo.h"
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

float forwardAcceleration = 1;

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






// the 'setup' function
void initStage00() {  
  // the advantage of initializing these values here, rather than statically, is
  // that if you switch stages/levels, and later return to this stage, you can
  // call this function to reset these values.


  // In the older version of C used by the N64 compiler (roughly C89); variables
  // must be declared at the top of a function or block scope. This is an example
  // of using block scope to declare a variable in the middle of a function.

}

// the 'update' function
void updateGame00() {
  // read controller input from controller 1 (index 0)
  nuContDataGetEx(contdata, 0);


  float joystickMagnitude = sqrtf(contdata[0].stick_y * contdata[0].stick_y + contdata[0].stick_x * contdata[0].stick_x);
  if (contdata[0].button & A_BUTTON && (forwardVelocity < forwardMax)){
    forwardVelocity = forwardVelocity + forwardAcceleration;
  }

  if (contdata[0].button & B_BUTTON && (forwardVelocity > forwardMin)){
    forwardVelocity = forwardVelocity - forwardAcceleration;
  }

  if(contdata[0].button & U_CBUTTONS){
      forwardVelocity = 0;
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


  cameraPos.x = cameraPos.x + (cameraForward.x * forwardVelocity * .016);
  cameraPos.y = cameraPos.y + (cameraForward.y * forwardVelocity * .016);
  cameraPos.z = cameraPos.z + (cameraForward.z * forwardVelocity * .016);

  cameraTarget.x = cameraPos.x + cameraForward.x;
  cameraTarget.y = cameraPos.y + cameraForward.y;
  cameraTarget.z = cameraPos.z + cameraForward.z;
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
  //gSPDisplayList(displayListPtr++, cube_dl);
  //gSPDisplayList(displayListPtr++, cube_dl);

    /*for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j++){
            debug_printf("%f ", skyboxTranslation[i][j]);

            if(j % 4 == 0 && j % 4 != 2){
                debug_printf("\n");
            }
        }
    }*/
    //debug_printf("\n");


    //guTranslate(&skyboxTranslation, cameraPos.x, cameraPos.y, cameraPos.z);
    //gSPMatrix(displayListPtr++, &skyboxTranslation, G_MTX_MODELVIEW | G_MTX_PUSH);
    guTranslate(&skyboxTranslation, cameraPos.x, cameraPos.y, cameraPos.z);
    gSPMatrix(displayListPtr++, &skyboxTranslation, G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);
    if(skyboxOn > -1) {
        gSPDisplayList(displayListPtr++, skybox_dl);
        debug_printf("draw_skybox");
    }
    //gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);
    gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);
    gSPDisplayList(displayListPtr++, ufo_Cube_mesh);
    //gSPDisplayList(displayListPtr++, Wtx_speaker);


    gDPPipeSync(displayListPtr++);
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
    NU_GFX_UCODE_F3DEX, // load the 'F3DEX' version graphics microcode, which runs on the RCP to process this display list
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

void drawSkybox(){
    /*guTranslateF(skyboxTranslation, cameraPos.x, cameraPos.y, cameraPos.z);
    gSPMatrix(displayListPtr++, &skyboxTranslation, G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);
    gSPDisplayList(displayListPtr++, cube_dl);
    gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);*/

    /*gDPLoadSync(displayListPtr++);
    gSPTexture(displayListPtr++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureFilter(displayListPtr++, G_TF_POINT);
    gDPSetTexturePersp(displayListPtr++, G_TP_PERSP);
    gDPSetCombineMode(displayListPtr++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPSetTextureLUT(displayListPtr++, G_TT_RGBA16);

    gDPSetCycleType(displayListPtr++, G_CYC_2CYCLE);
    gDPSetRenderMode(displayListPtr++, G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2);
    gSPClearGeometryMode(displayListPtr++,0xFFFFFFFF);
    gSPSetGeometryMode(displayListPtr++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER);
    //Translate the skybox with the camera
    guTranslate(&skyboxTranslation, cameraPos.x, cameraPos.y, cameraPos.z);


    gSPMatrix(displayListPtr++, &skyboxTranslation, G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);
    gDPLoadTLUT_pal16(displayListPtr++, 0, tileable_space_texture_tlut);
    gDPLoadTextureBlock_4b(displayListPtr++, space_texture, G_IM_FMT_CI, 64, 64, 0, G_TX_WRAP, G_TX_WRAP,
                           6, 6, 0, 0);
    //gDPTileSync(displayListPtr++);
    //gdPLoadSync(displayListPtr++);
    gSPVertex(displayListPtr++, skybox_vertices + 0, 16, 0);
    gSP1Triangle(displayListPtr++, 0, 1, 2, 0);
    gSP1Triangle(displayListPtr++, 0, 2, 3, 0);


    gSP1Triangle(displayListPtr++, 4, 5, 6, 0);
    gSP1Triangle(displayListPtr++, 4, 6, 7, 0);



    gSP1Triangle(displayListPtr++,8, 9, 10, 0);
    gSP1Triangle(displayListPtr++,8, 10, 11, 0);


    gSP1Triangle(displayListPtr++,12, 13, 14, 0);
    gSP1Triangle(displayListPtr++,12, 14, 15, 0);



    gSPVertex(displayListPtr++, skybox_vertices + 16, 8, 0);
    gSP1Triangle(displayListPtr++,0, 1, 2, 0);
    gSP1Triangle(displayListPtr++,0, 2, 3, 0);



    gSP1Triangle(displayListPtr++,4, 5, 6, 0);
    gSP1Triangle(displayListPtr++,4, 6, 7, 0);




    gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);
    gDPPipeSync(displayListPtr++);*/
}

