#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <game.h>
#include <macros.h>
#include <loaders.h>
#include <pipepair.h>
#include <base.h>
#include <configs.h>
#include <bird.h>

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
    .Bases    = {},
    .Start    = false,
  };

  /* initializing pipes starting from
   * end of the screen */
  int xPos = WIDTH;
  for (size_t i = 0; i < PIPES; i++) {
    PipePairSpawn(&game->Pipes[i], xPos);
    xPos += HGAP;
  }

  xPos = 0;
  for (size_t i = 0; i < BASES; i++) {
    BaseSpawn(&game->Bases[i], xPos);
    xPos += BASE_WIDTH; 
  }

  BirdSpawn(&game->Bird);

  return game;
}

void GameDestroy(Game** pGame) {
  if (!*pGame)
    return;

  Game* game = *pGame;
  for (size_t i = 0; i < _TextureCount_; i++) {
    SDL_DestroyTexture(game->Textures[i]);
  }
  free(game);
  *pGame = NULL;
}

int GameUpdate(Game* game) {
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
    const size_t lookup = LOOKUP(i, PIPES);

    /* wait for the Pipe to go smoothly
      * out the window */
    if (pp->XPos <= -(PIPE_WIDTH)) {
      PipePairSpawn(
        pp,
        game->Pipes[lookup].XPos + HGAP
      );
    }

    /* draw pipes only when they are inside the window */
    if (pp->XPos >= -(PIPE_WIDTH) && pp->XPos <= WIDTH) {
      PipePairDraw(pp, game->Renderer, game->Textures[TexturePipeGreen]);
    }

    if (game->Start) {
      PipePairMove(pp);
    }
  }

  for (size_t i = 0; i < BASES; i++) {
    Base* b = &game->Bases[i];
    /* if i == 0, then we lookup the last
     *  base in the bases array,
     *  i.e, BASES - 1 for 0 else i - 1 */
    const size_t lookup = LOOKUP(i, BASES);
    const int prevBaseXPos = game->Bases[lookup].XPos;

    /* if pos + BASE_WIDTH < WIDTH 
     *  then that means a base scrolled towards
     *  left and we need to put another base after it */
    if (prevBaseXPos + BASE_WIDTH < WIDTH &&
          b->XPos != prevBaseXPos + BASE_WIDTH) {
      BaseSpawn(b, prevBaseXPos + BASE_WIDTH);
    }
    
    BaseDraw(b, game->Renderer, game->Textures[TextureBase]);
    if (game->Start) {
      BaseMove(b);
    }
  }
  

  /* Next flap */
  if (game->Bird.FlapDuation >= BIRD_MAX_FLAP_DURATION) {
    game->Bird.Flap = LOOKUP(game->Bird.Flap, _BirdFlapCount_);
    game->Bird.FlapDuation = 0;
  }
    
  game->Bird.FlapDuation++;

  BirdDraw(
    &game->Bird,
    game->Renderer,
    /* Cycles through different flaps */
    game->Textures[TextureYellowBirdDownFlap + game->Bird.Flap]
  );
  if (game->Start) {
    BirdMove(&game->Bird);
  }

  return ret;
}

