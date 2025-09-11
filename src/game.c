#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <game.h>
#include <macros.h>
#include <loaders.h>
#include <pipepair.h>

struct Game {
  SDL_Renderer*       Renderer;
  SDL_Texture* const* Textures;
  PipePair            Pipes[PIPES];
};

Game* GameCreate(SDL_Renderer* renderer) {
  SDL_Texture* const* textures = LoadTextures(renderer);
  if (!textures)
    return NULL;

  /* seed for random generator */
  srand(time(NULL));

  Game* game = malloc(sizeof(*game));
  *game = (Game){
    .Renderer = renderer,
    .Textures = textures,
    .Pipes    = {},
  };

  /* initializing pipes starting from
   * center of the screen */
  int xPos = WIDTH / 2;
  for (size_t i = 0; i < PIPES; i++) {
    PipePairSpawn(&game->Pipes[i], xPos);
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

  /* Background Day */
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
    PipePair* pp = &game->Pipes[i];
    /* if i == 0, then we lookup the last
     *  pipe in the pipes array,
     *  i.e, PIPES - 1 for 0 else i - 1 */
    const size_t lookup = i == 0 ? PIPES - 1 : i - 1;

    /* wait for the Pipe to go smoothly
      * out the window */
    if (pp->xPos <= -(PIPE_WIDTH)) {
      PipePairSpawn(
        pp,
        game->Pipes[lookup].xPos + HGAP
      );
    }

    PipePairDraw(pp, game->Renderer, game->Textures[TexturePipeGreen]);
    PipePairMove(pp);
  }

  SDL_RenderPresent(game->Renderer);
  /* 10 ms */
  usleep(10 * 1000);
  return ret;
}

