#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

typedef struct Game Game;

Game* GameCreate(SDL_Renderer*);
void  GameDestroy(Game**);
int   GameUpdate(Game*, SDL_Event*);

#endif
