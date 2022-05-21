#ifndef GAME_OF_LIFE_INTERFACE_H
#define GAME_OF_LIFE_INTERFACE_H

#include "SDL2/SDL.h"
#include <stdbool.h>

//initialize SDL
bool init();

SDL_Texture *loadTexture(char *path, SDL_Renderer *renderer);

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void drawWorld(char **world, unsigned int row, unsigned int column, float unitLength);

void closeSDL();

#endif //GAME_OF_LIFE_INTERFACE_H
