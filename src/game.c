#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/game.h"
#include "../include/utility.h"
#include "../include/interface.h"
#include "../include/fileIO.h"

void freeWorld(char **world) {
    for (int i = 0; i < row; i++) {
        free(world[i]);
        world[i] = NULL;
    }
    free(world);
    world = NULL;
}

bool compareWorld(char **world, char **newWorld) {
    int numEqual = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (world[i][j] == newWorld[i][j]) {
                numEqual++;
            }
        }
    }
    if (numEqual == (row * column)) {
        return true;
    } else {
        return false;
    }
}

char **nextGeneration(char **world) {
    char **newWorld = (char **) malloc(sizeof(char *) * row);
    for (int i = 0; i < row; i++) {
        newWorld[i] = (char *) malloc(sizeof(char) * column);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            newWorld[i][j] = world[i][j];
        }
    }
    int num;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            num = 0;
            for (int m = -1; m < 2; m++) {
                for (int n = -1; n < 2; n++) {
                    if (!(m == 0 && n == 0)) {
                        if (i + m >= 0 && i + m < row && j + n >= 0 && j + n < column) {
                            if (world[i + m][j + n] == '1') {
                                num++;
                            }
                        }
                    }
                }
            }
            if (world[i][j] == '1') {
                if (num != 2 && num != 3) {
                    newWorld[i][j] = '0';
                }
            } else {
                if (num == 3) {
                    newWorld[i][j] = '1';
                }
            }
        }
    }
    return newWorld;
}

void game(char *fileName, char **world) {

    char *evolveNumberString = (char *) malloc(sizeof(char) * 120);
    printf("Please enter the number of steps to evolve\n(enter the letter 'q' means not to specify the number)\n->");
    scanf("%s", evolveNumberString);
    while (isNumber(evolveNumberString) == false && strcmp(evolveNumberString, "q") != 0) {
        printf("Invalid choice!\nPlease enter a number or the letter 'q':\n->");
        scanf("%s", evolveNumberString);
    }
    int specifyEvolve;
    if (strcmp(evolveNumberString, "q") == 0) {
        specifyEvolve = -1;
    } else {
        specifyEvolve = atoi(evolveNumberString);
    }


    SDL_Event initEvent;
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&initEvent)) {
            switch (initEvent.type) {
                case SDL_QUIT:
                    quit = true;
            }
        } else {
            drawWorld(world, row, column, unitLength);
        }
    }

    quit = false;

    SDL_Event e;
    int steps = 0;
    int leftEvolve = specifyEvolve;
    char **newWorld = NULL;
    int flag = 1;
    int tag = 1;
    while (!quit) {
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                default:
                    break;
            }
        } else {
            if (specifyEvolve == -1) {
                newWorld = nextGeneration(world);
                if (compareWorld(world, newWorld)) {
                    printf("A total of %d rounds of cell evolution is stabilized.\n", steps);
                    freeWorld(newWorld);
                    while (SDL_WaitEvent(&e)) {
                        switch (e.type) {
                            case SDL_QUIT:
                                closeSDL();
                                tag = 0;
                                quit = true;
                                break;
                            default:
                                break;
                        }
                    }
                }
                if (tag == 1) {
                    freeWorld(world);
                    world = newWorld;
                    newWorld = NULL;
                    SDL_Delay(300);
                    drawWorld(world, row, column, unitLength);
                }
                steps++;
            } else {
                newWorld = nextGeneration(world);
                if (compareWorld(world, newWorld)) {
                    printf("A total of %d rounds of cell evolution is stabilized.\n", steps);
                    freeWorld(newWorld);
                    while (SDL_WaitEvent(&e)) {
                        switch (e.type) {
                            case SDL_QUIT:
                                closeSDL();
                                tag = 0;
                                quit = true;
                                break;
                            default:
                                break;
                        }
                    }
                } else if (leftEvolve == 0) {
                    printf("按照要求，一共迭代了%d次。\n", specifyEvolve);
                    freeWorld(newWorld);
                    while (SDL_WaitEvent(&e)) {
                        switch (e.type) {
                            case SDL_QUIT:
                                closeSDL();
                                tag = 0;
                                quit = true;
                                break;
                            default:
                                break;
                        }
                    }
                }
                if (tag == 1) {
                    freeWorld(world);
                    world = newWorld;
                    newWorld = NULL;
                    SDL_Delay(300);
                    drawWorld(world, row, column, unitLength);
                }
                steps++;
                leftEvolve--;
            }
        }
    }

    storeWorld(fileName, world, row, column);
    freeWorld(world);

    free(evolveNumberString);
    evolveNumberString = NULL;
}