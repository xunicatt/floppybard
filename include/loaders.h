#ifndef LOADERS_H_
#define LOADERS_H_

#include <SDL.h>

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

SDL_Texture* const* LoadTextures(SDL_Renderer*);

#endif

