#include <bird.h>
#include <configs.h>
#include <macros.h>

void BirdSpawn(Bird* b) {
  b->YPos = HEIGHT / 2;
  b->FutureYPos = b->YPos;
  b->Flap = BirdFlagMid;
}

int BirdDraw(Bird* b, SDL_Renderer* renderer, SDL_Texture* birdTexture) {
  int ret = 0;

  const SDL_Rect box = SDL_RECT_FROM_CENTER(
    WIDTH/2,
    b->YPos,
    50,
    50
  );

  ret = SDL_RenderCopy(
    renderer,
    birdTexture,
    NULL,
    &box
  );

  return ret;
}

void BirdMove(Bird* b) {
  if (b->YPos != b->FutureYPos) {
    b->YPos -= 5;
    return;
  }

  b->YPos += 1;
  b->FutureYPos = b->YPos;
}

void BirdFlight(Bird* b) {
  if (b->FutureYPos !=  b->YPos) {
    b->FutureYPos = b->YPos;
  }

  b->FutureYPos -= BIRD_JUMP_OFFSET;
}
