#include <pipepair.h>
#include <unistd.h>
#include <configs.h>
#include <macros.h>

void PipePairSpawn(PipePair* pp, const int xPos) {
  const int offset = (rand() % PIPE_MAX_OFFSET) - PIPE_MAX_OFFSET;
    
  pp->TopPipePos = offset;
  pp->BottomPipePos = pp->TopPipePos + PIPE_HEIGHT + VGAP;
  pp->XPos = xPos;
}

int PipePairDraw(const PipePair* pp, SDL_Renderer* renderer, SDL_Texture* pipeTexture) {
  int ret = 0;
  const struct SDL_Rect pipeTop = {
    .x = pp->XPos,
    .y = pp->TopPipePos,
    .h = PIPE_HEIGHT,
    .w = PIPE_WIDTH,
  };

  const struct SDL_Rect pipeBottom = {
    .x = pp->XPos,
    .y = pp->BottomPipePos,
    .h = PIPE_HEIGHT,
    .w = PIPE_WIDTH,
  };

  /* 180 deg rotation of pipe texture */
  ret = SDL_RenderCopyEx(
    renderer,
    pipeTexture,
    NULL, 
    &pipeTop,
    180,
    NULL,
    SDL_FLIP_HORIZONTAL
  );
  if (ret < 0) {
    LOG_ERROR("failed to copy top pipe texture: %s", SDL_GetError());
    return ret;
  }

  ret = SDL_RenderCopy(
    renderer,
    pipeTexture,
    NULL, 
    &pipeBottom
  );
  if (ret < 0) {
    LOG_ERROR("failed to copy bottom pipe texture: %s", SDL_GetError());
    return ret;
  }

  return ret;
}

void PipePairMove(PipePair* pp) {
  /* move from right to left */
  pp->XPos--;
}

