#ifndef BIRD_H_
#define BIRD_H_

#include <SDL.h>

typedef enum {
  BirdFlapDown = 0,
  BirdFlapMid,
  BridFlapUp,
  _BirdFlapCount_,
} BirdFlap;

typedef struct {
  BirdFlap Flap;
  int FutureYPos;
  int YPos;
  int FlyDuration;
  int FlapDuation;
} Bird;

void BirdSpawn(Bird*);
int  BirdDraw(Bird*, SDL_Renderer*, SDL_Texture* birdTexture);
void BirdMove(Bird*);
void BirdFlight(Bird*);

#endif

