#include <pipepair.h>
#include <macros.h>
#include <unistd.h>

void PipePairSpawn(PipePair* pp, int xPos) {
  /* -70 to 0 */
  /* 70 is calculated from: 
  *   (2 * 320)[Two Pipes] + 100 [VGap between them] - (600)[Window Height]
  *     = 140
  *   So either way we have 140/2 or 70 pixels to offset */
  const int offset = (rand() % PIPE_MAX_OFFSET) - PIPE_MAX_OFFSET;
    
  pp->TopPipePos = offset;
  pp->BottomPipePos = pp->TopPipePos + PIPE_HEIGHT + VGAP;
  pp->xPos = xPos;
}

int PipePairDraw(const PipePair* pp, SDL_Renderer* renderer, SDL_Texture* pipeTexture) {
  int ret = 0;
  const struct SDL_Rect pipeTop = {
    .x = pp->xPos,
    .y = pp->TopPipePos,
    .h = PIPE_HEIGHT,
    .w = PIPE_WIDTH,
  };

  const struct SDL_Rect pipeBottom = {
    .x = pp->xPos,
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
  pp->xPos--;
}

