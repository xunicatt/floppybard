#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include <SDL.h>
#include <bird.h>
#include <base.h>
#include <pipepair.h>
#include <configs.h>

typedef struct {
  SDL_Renderer*       Renderer;
  SDL_Texture* const* Textures;
  PipePair            Pipes[PIPES];
  Base                Bases[BASES];
  Bird                Bird;
  bool Start;
} Game ;

Game* GameCreate(SDL_Renderer*);
void  GameDestroy(Game**);
int   GameUpdate(Game*);

#endif

