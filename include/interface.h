#ifndef GAME_OF_LIFE_INTERFACE_H
#define GAME_OF_LIFE_INTERFACE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
//initialize SDL
bool init();

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void drawWorld(char** world, int row, int column, float unitLength);

void closeSDL();

#endif //GAME_OF_LIFE_INTERFACE_H
