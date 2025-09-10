#include "SDL_render.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <game.h>
#include <macros.h>
#include <unistd.h>
#include <time.h>

typedef enum {
  TextureZero = 0,
  TextureOne,
  TextureTwo,
  TextureThree,
  TextureFour,
  TextureFive,
  TextureSix,
  TextureSeven,
  TetxureEight,
  TextureNine,
  TextureBackgroundDay,
  TextureBackgroundNight,
  TextureBase,
  TextureBlueBirdDownFlap,
  TextureBlueBirdMidFlap,
  TextureBlueBirdUpFlap,
  TextureGameover,
  TextureMessage,
  TexturePipeGreen,
  TexturePipeRed,
  TextureRedBirdDownFlap,
  TextureRedBirdMidFlap,
  TextureRedBirdUpFlap,
  TextureYellowBirdDownFlap,
  TextureYellowBirdMidFlap,
  TextureYellowBirdUpFlap,
  _TextureCount_
} GameTextures;

typedef struct {
  int TopPipePos;
  int BottomPipePos;
  int xPos;
} PipePair;

struct Game {
  SDL_Renderer*       Renderer;
  SDL_Texture* const* Textures;
  PipePair            Pipes[PIPES];
};

static SDL_Texture* const* LoadTextures(SDL_Renderer*);
static void                GameSpawnPipe(Game*, size_t, int);
static int                 GameDrawPipe(Game*, size_t);
static void                GameMovePipe(Game*, size_t);

Game* GameCreate(SDL_Renderer* renderer) {
  SDL_Texture* const* textures = LoadTextures(renderer);
  if (!textures)
    return NULL;

  srand(time(NULL));

  Game* game = malloc(sizeof(*game));
  *game = (Game){
    .Renderer = renderer,
    .Textures = textures,
    .Pipes    = {},
  };

  int xPos = WIDTH / 2;
  for (size_t i = 0; i < PIPES; i++) {
    GameSpawnPipe(game, i, xPos);
    xPos += HGAP;
  }

  return game;
}

void GameDestroy(Game** pGame) {
  if (!*pGame)
    return;

  Game* game = *pGame;
  free(game);
  *pGame = NULL;
}

int GameUpdate(Game* game, SDL_Event* event) {
  ARG_UNUSED(event);
  int ret = 0;
  const SDL_Rect bgRect = { 
    .x = 0, 
    .y = 0,
    .w = WIDTH,
    .h = HEIGHT
  };

  ret = SDL_RenderCopy(
    game->Renderer,
    game->Textures[TextureBackgroundDay],
    NULL, 
    &bgRect
  );
  if (ret < 0) {
    LOG_ERROR("failed to copy background texture: %s", SDL_GetError());
    return ret;
  }

  for (size_t i = 0; i < PIPES; i++) {
    const PipePair* pp = &game->Pipes[i];
    const size_t lookup = i == 0 ? PIPES - 1 : i - 1;
    if (pp->xPos <= -(PIPE_WIDTH)) {
      GameSpawnPipe(
        game,
        i,
        game->Pipes[lookup].xPos + HGAP
      );
    }

    GameDrawPipe(game, i);
    GameMovePipe(game, i);
  }

  SDL_RenderPresent(game->Renderer);
  usleep(10 * 1000);
  return ret;
}

void GameSpawnPipe(Game* game, size_t i, int xPos) {
  PipePair* pp     = &game->Pipes[i];
  const int offset = (rand() % PIPE_MAX_OFFSET) - PIPE_MAX_OFFSET;
    
  pp->TopPipePos = offset;
  pp->BottomPipePos = pp->TopPipePos + PIPE_HEIGHT + VGAP;
  pp->xPos = xPos;
}

int GameDrawPipe(Game* game, size_t i) {
  int ret = 0;
  const PipePair* pp = &game->Pipes[i];
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

  ret = SDL_RenderCopyEx(
    game->Renderer,
    game->Textures[TexturePipeGreen],
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
    game->Renderer,
    game->Textures[TexturePipeGreen],
    NULL, 
    &pipeBottom
  );
  if (ret < 0) {
    LOG_ERROR("failed to copy bottom pipe texture: %s", SDL_GetError());
    return ret;
  }

  return ret;
}

void GameMovePipe(Game* game, size_t i) {
  PipePair* pp = &game->Pipes[i];
  pp->xPos--;
}

SDL_Texture* const* LoadTextures(SDL_Renderer* renderer) {
  static const size_t size = 128;
  static char buffer[128] = {};
  static SDL_Texture* textures[_TextureCount_] = {};
  static const char* pngFiles[_TextureCount_] = {
    "0.png",
    "1.png",
    "2.png",
    "3.png",
    "4.png",
    "5.png",
    "6.png",
    "7.png",
    "8.png",
    "9.png",
    "background-day.png",
    "background-night.png",
    "base.png",
    "bluebird-downflap.png",
    "bluebird-midflap.png",
    "bluebird-upflap.png",
    "gameover.png",
    "message.png",
    "pipe-green.png",
    "pipe-red.png",
    "redbird-downflap.png",
    "redbird-midflap.png",
    "redbird-upflap.png",
    "yellowbird-downflap.png",
    "yellowbird-midflap.png",
    "yellowbird-upflap.png",
  };

  size_t i = 0;
  while (i < _TextureCount_) {
    snprintf(buffer, size - 1, "assets/sprites/%s", pngFiles[i]);
    textures[i] = IMG_LoadTexture(renderer, buffer);
    if (!textures[i]) {
      LOG_ERROR("failed to load texture: %s", SDL_GetError());
      goto cleanup;
    }
    i++;
  }

  return textures;

cleanup:
  while (i-- > 0)
    SDL_DestroyTexture(textures[i - 1]);
  return NULL;
}
