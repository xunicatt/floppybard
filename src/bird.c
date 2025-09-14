#include <bird.h>
#include <configs.h>
#include <macros.h>

void BirdSpawn(Bird* b) {
  b->YPos = HEIGHT / 2;
  b->FutureYPos = b->YPos;
  b->Flap = BirdFlapDown;
  b->FlyDuration = BIRD_MAX_FLY_DURATION;
  b->FlapDuation = 0;
}

int BirdDraw(Bird* b, SDL_Renderer* renderer, SDL_Texture* birdTexture) {
  int ret = 0;

  const SDL_Rect box = SDL_RECT_FROM_CENTER(
    WIDTH/2,
    b->YPos,
    50,
    50
  );
  
  /* converts 0 .. Height into -90 to 90 range */
  const double angle = (
    (b->YPos / (double)HEIGHT) * (BIRD_MAX_DOWN_TILT - BIRD_MAX_UP_TILT)
  ) + BIRD_MAX_UP_TILT; 

  ret = SDL_RenderCopyEx(
    renderer,
    birdTexture,
    NULL,
    &box,
    angle,
    NULL,
    SDL_FLIP_NONE
  );
    
  return ret;
}

void BirdMove(Bird* b) {
  if (b->YPos > b->FutureYPos) {
    b->YPos -= BIRD_ACCELERATION;
    return;
  }
  
  if (b->YPos >= b->FutureYPos && b->FlyDuration < BIRD_MAX_FLY_DURATION) {
    b->FlyDuration++;
    return;
  }

  /* dont under shoot the bird to earth's core*/
  if (b->YPos < (HEIGHT - BIRD_DEACCELERATION)) {
    b->YPos += BIRD_DEACCELERATION;
    b->FutureYPos = b->YPos;
  }
}

void BirdFlight(Bird* b) {
  /* dont over shoot the bird to moon */
  if (b->FutureYPos > BIRD_JUMP_OFFSET) {
    b->FutureYPos -= BIRD_JUMP_OFFSET;
  }
  b->FlyDuration = 0;
}

