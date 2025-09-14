#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <game.h>
#include <macros.h>
#include <configs.h>
#include <bird.h>

int main(void) {
  int ret = 0;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  ret = SDL_Init(SDL_INIT_VIDEO);
  if (ret < 0) {
    LOG_ERROR("failed to initialize SDL: %s", SDL_GetError());
    return -1;
  }

  ret = TTF_Init();
  if (ret < 0) {
    LOG_ERROR("failed to initialize TTF: %s", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  ret = IMG_Init(IMG_INIT_PNG);
  if ((ret & IMG_INIT_PNG) == 0) {
    LOG_ERROR("failed to initialize IMG: %s", SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    return -1;
  }

  window = SDL_CreateWindow(
    "floppy bard",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN 
  );
  if (!window) {
    LOG_ERROR("failed to create window: %s", SDL_GetError());
    goto cleanup;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (!renderer) {
    LOG_ERROR("failed to create renderer: %s", SDL_GetError());
    goto cleanup;
  }

  Game* game = GameCreate(renderer);
  if (!game)
    goto cleanup;

  SDL_Event event = {};
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      /* quit if ESC key is pressed */
      if (event.type == SDL_QUIT || IS_KEYDOWN(&event, SDLK_ESCAPE)) {
        quit = true;
      }

      if (IS_KEYDOWN(&event, SDLK_SPACE) || IS_BUTTONDOWN(&event, SDL_BUTTON_LEFT)) {
        if (!game->Start) {
          game->Start = true;
        }
        BirdFlight(&game->Bird);
      }
    }

    ret = GameUpdate(game);
    if (ret < 0) {
      LOG_ERROR("failed to update game");
      quit = true;
    }
  }

  GameDestroy(&game);

cleanup:
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return ret;
}

