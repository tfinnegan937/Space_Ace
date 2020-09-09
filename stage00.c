
#include <assert.h>
#include <nusys.h>
#include "gu.h"

#include "graphic.h"
#include "main.h"
#include "stage00.h"
#include "n64logo.h"
#include "skybox.h"
#include "space_texture.h"
#include "red_texture.h"

Vec3d cameraPos = {-200.0f, -200.0f, -200.0f};
Vec3d cameraTarget = {-199, -199, -199};
Vec3d cameraForward = {0.0f, 0.0f, 1.0f};
Vec3d cameraEulerAngles = {0.0f, 0.0f, 0.0f};
Vec3d cameraUp = {0.0f, 1.0f, 0.0f};
Vec3d cameraLeft = {1.0f, 0.0f, 0.0f};

//booleans
char pitch = 0;
char roll = 0;
char yaw = 0;

char yawDirection = 1;
char rollDirection = 1;
char pitchDirection = 1;

float yawVelocity = 127;
float pitchVelocity = 127;
float rollVelocity = 127;

float forwardVelocity = 0;
float forwardMin = -100;
float forwardMax = 100;

float forwardAcceleration = 1;

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


// the positions of the squares we're gonna draw
#define NUM_SQUARES 5
struct Vec3d squares[NUM_SQUARES] = {
  {0.0f, 0.0f, 0.0f},
  {0.0f, 0.0f, 0.0f},
  {0.0f, 0.0f, 0.0f},
  {0.0f, 0.0f, 200.0f},
  {0.0f, 0.0f, -100.0f},
};

int squaresRotations[NUM_SQUARES];
int initSquaresRotations[NUM_SQUARES] = {
  0,
  20,
  40,
  40,
  40,
};

// this is a boolean but the older version of C used by the N64 compiler
// (roughly C89), doesn't have a bool type, so we just use integers
int squaresRotationDirection;

int showN64Logo;

// the 'setup' function
void initStage00() {  
  // the advantage of initializing these values here, rather than statically, is
  // that if you switch stages/levels, and later return to this stage, you can
  // call this function to reset these values.
  squaresRotationDirection = FALSE;
  showN64Logo = FALSE;

  // In the older version of C used by the N64 compiler (roughly C89), variables
  // must be declared at the top of a function or block scope. This is an example
  // of using block scope to declare a variable in the middle of a function.
  {
    int i;
    for (i = 0; i < NUM_SQUARES; ++i) {
      squaresRotations[i] = initSquaresRotations[i];
    }
  }
}

// the 'update' function
void updateGame00() {
  // read controller input from controller 1 (index 0)
  nuContDataGetEx(contdata, 0);
  // We check if the 'A' Button was pressed using a bitwise AND with
  // contdata[0].trigger and the A_BUTTON constant.
  // The contdata[0].trigger property is set only for the frame that the button is
  // initially pressed. The contdata[0].button property is similar, but stays on
  // for the duration of the button press.

  float joystickMagnitude = sqrtf(contdata[0].stick_y * contdata[0].stick_y + contdata[0].stick_x * contdata[0].stick_x);
  if (contdata[0].button & A_BUTTON && (forwardVelocity < forwardMax)){
    // when A button is pressed, reverse rotation direction
    forwardVelocity = forwardVelocity + forwardAcceleration;
  }

  if (contdata[0].button & B_BUTTON && (forwardVelocity > forwardMin)){
    // when B button is held, change squares into n64 logos
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
  yaw = 0;
  if(contdata[0].stick_x !=0 && (joystickMagnitude >=40)){

      yaw = 1;
      yawDirection = contdata[0].stick_x / sqrtf(contdata[0].stick_x * contdata[0].stick_x);
  }
  pitch = 0;
  if(contdata[0].stick_y !=0 && (joystickMagnitude >=40)){
    pitch = 1;
    pitchDirection = contdata[0].stick_y / sqrtf(contdata[0].stick_y * contdata[0].stick_y);
  }



  //Perform the transformations






  // update square rotations
  {
    int i;
    for (i = 0; i < NUM_SQUARES; ++i)
    {
      squaresRotations[i] = (squaresRotations[i] + (squaresRotationDirection ? 1 : -1)) % 360;
    }
  }

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
  drawSkybox();

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
  {
    int i;
    Vec3d* square;
    for (i = 0; i < NUM_SQUARES; ++i)
    {
      square = &squares[i];
      // create a transformation matrix representing the position of the square
      guPosition(
        &gfxTask->objectTransforms[i],
        // rotation
        squaresRotations[i], // roll
        0.0f, // pitch
        0.0f, // heading
        1.0f, // scale
        // position
        square->x, square->y, square->z
      );



      // push relative transformation matrix
      gSPMatrix(displayListPtr++,
        OS_K0_TO_PHYSICAL(&(gfxTask->objectTransforms[i])),
        G_MTX_MODELVIEW | // operating on the modelview matrix stack...
        G_MTX_PUSH | // ...push another matrix onto the stack...
        G_MTX_MUL // ...which is multipled by previously-top matrix (eg. a relative transformation)
      );
      if (!showN64Logo) {
        //drawN64Logo();
      } else {
        drawSquare();
      }

      // pop the matrix that we added back off the stack, to move the drawing position 
      // back to where it was before we rendered this object
      gSPPopMatrix(displayListPtr++, G_MTX_MODELVIEW);
    }
  }

  // mark the end of the display list
  gDPFullSync(displayListPtr++);
  gSPEndDisplayList(displayListPtr++);

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


// A static array of model vertex data.
// This include the position (x,y,z), texture U,V coords (called S,T in the SDK)
// and vertex color values in r,g,b,a form.
// As this data will be read by the RCP via direct memory access, which is
// required to be 16-byte aligned, it's a good idea to annotate it with the GCC
// attribute `__attribute__((aligned (16)))`, to force it to be 16-byte aligned.
Vtx squareVerts[] __attribute__((aligned (16))) = {
  //  x,   y,  z, flag, S, T,    r,    g,    b,    a
  { -64,  64, -5,    0, 0, 0, 0x00, 0xff, 0x00, 0xff  },
  {  64,  64, -5,    0, 0, 0, 0x00, 0x00, 0x00, 0xff  },
  {  64, -64, -5,    0, 0, 0, 0x00, 0x00, 0xff, 0xff  },
  { -64, -64, -5,    0, 0, 0, 0xff, 0x00, 0x00, 0xff  },
};

void drawSquare() {
  // load vertex data for the triangles
  gSPVertex(displayListPtr++, &(squareVerts[0]), 4, 0);
  // depending on which graphical features, the RDP might need to spend 1 or 2
  // cycles to render a primitive, and we need to tell it which to do
  gDPSetCycleType(displayListPtr++, G_CYC_1CYCLE);
  // use antialiasing, rendering an opaque surface
  gDPSetRenderMode(displayListPtr++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
  // reset any rendering flags set when drawing the previous primitive
  gSPClearGeometryMode(displayListPtr++,0xFFFFFFFF);
  // enable smooth (gourad) shading and z-buffering
  gSPSetGeometryMode(displayListPtr++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER);

  // actually draw the triangles, using the specified vertices
  gSP2Triangles(displayListPtr++,0,1,2,0,0,2,3,0);

  // Mark that we've finished sending commands for this particular primitive.
  // This is needed to prevent race conditions inside the rendering hardware in 
  // the case that subsequent commands change rendering settings.
  gDPPipeSync(displayListPtr++);
}

// this is an example of rendering a model defined as a set of static display lists
void drawN64Logo() {
  gDPSetCycleType(displayListPtr++, G_CYC_1CYCLE);
  gDPSetRenderMode(displayListPtr++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
  gSPClearGeometryMode(displayListPtr++,0xFFFFFFFF);
  gSPSetGeometryMode(displayListPtr++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER);
  
  // The gSPDisplayList command causes the RCP to render a static display list,
  // then return to this display list afterwards. These 4 display lists are
  // defined in n64logo.h, and were generated from a 3D model using a conversion
  // script.
  gSPDisplayList(displayListPtr++, N64Yellow_PolyList);
  gSPDisplayList(displayListPtr++, N64Red_PolyList);
  gSPDisplayList(displayListPtr++, N64Blue_PolyList);
  gSPDisplayList(displayListPtr++, N64Green_PolyList);

  gDPPipeSync(displayListPtr++);
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
    //Load the texture
    gSPClearGeometryMode(displayListPtr++, G_TEXTURE_GEN)
    gSPTexture(displayListPtr++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureFilter(displayListPtr++, G_TF_BILERP);
    gDPSetTexturePersp(displayListPtr++, G_TP_PERSP);
    gDPSetCombineMode(displayListPtr++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureLUT(displayListPtr++, G_TT_NONE);
    gDPLoadTextureBlock(displayListPtr++, space_texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP, G_TX_WRAP,
        5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPTileSync(displayListPtr++);
    //Load the model

    gDPSetCycleType(displayListPtr++, G_CYC_2CYCLE);
    gDPSetRenderMode(displayListPtr++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
    gSPClearGeometryMode(displayListPtr++,0xFFFFFFFF);
    gSPSetGeometryMode(displayListPtr++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER | G_CULL_FRONT);


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


    gDPPipeSync(displayListPtr++);
}

