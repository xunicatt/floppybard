#ifndef PIPEPAIR_H_
#define PIPEPAIR_H_

#include <SDL.h>

typedef struct {
  int TopPipePos;
  int BottomPipePos;
  int xPos;
} PipePair;

void PipePairSpawn(PipePair*, int xPos);
int  PipePairDraw(const PipePair*, SDL_Renderer*, SDL_Texture* pipeTexture);
void PipePairMove(PipePair*);

#endif

