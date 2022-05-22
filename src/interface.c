#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include <stdbool.h>
#include "../include/interface.h"


SDL_Window *window = NULL; // initialize the SDL_Window pointer which points to NULL
SDL_Renderer *renderer = NULL; // initialize the SDL_Renderer pointer which points to NULL
SDL_Texture *texture = NULL; // initialize the SDL_Texture pointer which points to NULL

/**
 * initialize the window, the renderer and the texture
 * the size of the window is fixed at (640*640) pixels
 *
 * @return true if the window, the renderer and the texture are initalized with no error
 *         otherwise false
 */
bool init() {
    int success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    // Initialize window
    window = SDL_CreateWindow("Game of Life",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 640,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//            SDL_RenderClear(renderer);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            } else {
                texture = loadTexture("../photo/background3.jpg", renderer);
                if (texture == NULL) {
                    printf("Texture could not initialize! SDL Error: %s\n", SDL_GetError());
                    success = false;
                } else {
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }

    return success;
}

/**
 * load the image to surface
 * generate the texture from the surface
 *
 * For example:
 * loadTexture("photo/background.png")
 * returns gTexture
 *
 * @param path is the relative path of the image
 * @return a pointer which points to SDL_Texture;
 *         NULL if the image not found or texture not build successfully
 */
SDL_Texture *loadTexture(char *path, SDL_Renderer *renderer) {
    SDL_Texture *gTexture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        printf("No such file: %s! Error: %s\n", path, IMG_GetError());
        return NULL;
    } else {
        //Create texture from surface pixels
        gTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (gTexture == NULL) {
            printf("Wrong to create texture! SDL Error: %s\n", SDL_GetError());
            return NULL;
        }
    }
    return gTexture;
}

/**
 * draw white squares to express live cells and black squares to express dead cells
 *
 * @param world a 2-dimensional array which stores the previous live states of cells.
 * @param row the number of rows in the world which is in the interval of [0, 65535]
 * @param column the number of columns in the world which is in the interval of [0, 65535]
 * @param unitLength the width of each small cell square, computed by 640.0/max(row, column)
 * @return nothing
 */
void drawWorld(char **world, unsigned int row, unsigned int column, float unitLength) {
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            SDL_Rect rect = {j * unitLength, i * unitLength, unitLength, unitLength};
            if (world[i][j] == '1') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}

/**
 * free the resources of SDL, texture, renderer and window
 */
void closeSDL() {
    SDL_DestroyTexture(texture);
    texture = NULL;

    //Destroy window
    SDL_DestroyRenderer(renderer);
    window = NULL;
    SDL_DestroyWindow(window);
    renderer = NULL;

    //Quit SDL
    IMG_Quit();
    SDL_Quit();
}
