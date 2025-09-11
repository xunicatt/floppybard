#ifndef BASE_H_
#define BASE_H_

#include <SDL.h>

typedef struct {
  int XPos;
} Base;

void BaseSpawn(Base*, const int xPos);
int  BaseDraw(const Base*, SDL_Renderer*, SDL_Texture* baseTexture);
void BaseMove(Base*);

#endif

