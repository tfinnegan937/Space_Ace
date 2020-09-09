
#ifndef _STAGE00_H_
#define _STAGE00_H_

#include "graphic.h"

void stage00(int);
void initStage00();

void drawSquare();
void drawN64Logo();
void drawSkybox();

void updateSkyboxVertices(Vtx * output_vertices);

#endif /* _STAGE00_H_ */



