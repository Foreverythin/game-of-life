#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/interface.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;


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
                texture = loadTexture("../photo/background.png");
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

SDL_Texture *loadTexture(char *path) {
    SDL_Texture *gTexture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        printf("No such file: %s! Error: %s\n", path, IMG_GetError());
    } else {
        //Create texture from surface pixels
        gTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (gTexture == NULL) {
            printf("Wrong to create texture! SDL Error: %s\n", SDL_GetError());
        }
    }

    return gTexture;
}

void drawWorld(char **world, int row, int column, float unitLength) {
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
//    drawButton(world);
    SDL_RenderPresent(renderer);
}

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

//void drawButton(char **world) {
//    SDL_Button button_begin;
//    SDL_Button button_pause;
//    SDL_Button button_continue;
//    SDL_Button button_nextStep;
//    SDL_Button button_speedUp;
//    SDL_Button button_slowDown;
//
//    strcpy(button_begin.text, "BEGIN");
//    button_begin.x = 675;
//    button_begin.y = 50;
//    button_begin.w = 90;
//    button_begin.h = 35;
//
//    memcpy(&button_pause, &button_begin, 36);
//    button_pause.y += 100;
//    memcpy(&button_continue, &button_begin, 36);
//    button_continue.y += 200;
//    memcpy(&button_nextStep, &button_begin, 36);
//    button_nextStep.y += 300;
//    memcpy(&button_speedUp, &button_begin, 36);
//    button_speedUp.y += 400;
//    memcpy(&button_slowDown, &button_begin, 36);
//    button_slowDown.y += 500;
//
//    SDL_Rect rect = {button_begin.x, button_begin.y, button_begin.w, button_begin.h};
//    SDL_Rect rect2 = {button_pause.x, button_pause.y, button_pause.w, button_pause.h};
//    SDL_Rect rect3 = {button_continue.x, button_continue.y, button_continue.w, button_continue.h};
//    SDL_Rect rect4 = {button_nextStep.x, button_nextStep.y, button_nextStep.w, button_nextStep.h};
//    SDL_Rect rect5 = {button_speedUp.x, button_speedUp.y, button_speedUp.w, button_speedUp.h};
//    SDL_Rect rect6 = {button_slowDown.x, button_slowDown.y, button_slowDown.w, button_slowDown.h};
//    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
//    SDL_RenderFillRect(renderer, &rect);
//    SDL_RenderFillRect(renderer, &rect2);
//    SDL_RenderFillRect(renderer, &rect3);
//    SDL_RenderFillRect(renderer, &rect4);
//    SDL_RenderFillRect(renderer, &rect5);
//    SDL_RenderFillRect(renderer, &rect6);
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderDrawRect(renderer, &rect);
//    SDL_RenderDrawRect(renderer, &rect2);
//    SDL_RenderDrawRect(renderer, &rect3);
//    SDL_RenderDrawRect(renderer, &rect4);
//    SDL_RenderDrawRect(renderer, &rect5);
//    SDL_RenderDrawRect(renderer, &rect6);
//}
