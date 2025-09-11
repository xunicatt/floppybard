#include <base.h>
#include <configs.h>

void BaseSpawn(Base* b, const int xPos) {
  b->XPos = xPos; 
}

int BaseDraw(const Base* b, SDL_Renderer* renderer, SDL_Texture* baseTexture) {
  int ret = 0;
  const SDL_Rect box = {
    .x = b->XPos,
    .y = HEIGHT,
    .h = BASE_HEIGHT,
    .w = BASE_WIDTH,
  };

  ret = SDL_RenderCopy(
    renderer,
    baseTexture,
    NULL,
    &box
  );

  return ret;
}

void BaseMove(Base* b) {
  /* move from right to left */
  b->XPos--;
}

