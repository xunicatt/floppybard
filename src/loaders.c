#include <SDL_image.h>
#include <loaders.h>
#include <macros.h>

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

