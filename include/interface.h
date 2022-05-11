#ifndef GAME_OF_LIFE_INTERFACE_H
#define GAME_OF_LIFE_INTERFACE_H

#include "SDL2/SDL.h"
#include <stdbool.h>

typedef struct st_SDL_Button {
    int x, y, w, h;
    char text[20];
} SDL_Button;

//initialize SDL
bool init();

SDL_Texture *loadTexture(char *path, SDL_Renderer *renderer);

extern SDL_Window *window;
extern SDL_Renderer *renderer;

//void drawButton(char** world);

void drawWorld(char **world, unsigned int row, unsigned int column, float unitLength);

void closeSDL();

#endif //GAME_OF_LIFE_INTERFACE_H
