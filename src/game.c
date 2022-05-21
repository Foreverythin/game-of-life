#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/game.h"
#include "../include/utility.h"
#include "../include/interface.h"
#include "../include/fileIO.h"

/**
 * free the space which was allocated in heap and was pointed by world and *world
 *
 * For example:
 * freeWorld(world)
 * returns nothing
 *
 * @param world is a 2-dimensional array which stores the live states of cells.
 * @return 0 if free successfully, otherwise -1.
 */
int freeWorld(char **world) {
    if (world == NULL) {
        return -1;
    }
    if (*world == NULL) {
        return -1;
    }
    for (int i = 0; i < row; i++) {
        free(world[i]);
        world[i] = NULL;
    }
    free(world);
    world = NULL;

    return 0;
}

/**
 * compare two 2-dimensional arrays to judge whether they are store the same live states of cells
 *
 * For example:
 * compareWorld(world, newWorld)
 * returns true
 *
 * @param world is one 2-dimensional array which stores the same live states of cells
 * @param newWorld is one 2-dimensional array which is the next generation of "world"
 * @return true if "world" and "newWorld" store the same live states of cells
 *         otherwise false
 *         when one pointer is NULL, also returns false
 */
bool compareWorld(char **world, char **newWorld, unsigned int row, unsigned int column) {
    if (world == NULL || newWorld == NULL) {
        return false;
    }
    if (*world == NULL || *newWorld == NULL) {
        return false;
    }
    if (row == 0 || column == 0) {
        return false;
    }
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

/**
 * generate the next generation of cells
 *
 * For example:
 * nextGeneration(world)
 * returns newWorld
 *
 * @param world a 2-dimensional array which stores the previous live states of cells.
 * @return a 2-dimensional array which stores the live states of the next generation's cells;
 *         NULL if world points to NULL or *world points to NULL
 */
char **nextGeneration(char **world) {
    if (world == NULL) {
        return NULL;
    }
    if (*world == NULL) {
        return NULL;
    }
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

/**
 * Make each cell dead
 * Clear the screen
 *
 * @param world a 2-dimensional array which stores the live states of cells.
 * @return 0 if clear successfully, otherwise -1.
 */
int clearScreen(char **world) {
    if (world == NULL) {
        return -1;
    } else if (*world == NULL) {
        return -1;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            world[i][j] = '0';
        }
    }

    return 0;
}

/**
 * Produce a random world.
 * Each cell is randomly dead or alive.
 *
 * @param world a 2-dimensional array which stores the live states of cells.
 * @return 0 if produce a random world successfully, otherwise -1.
 */
int randomScreen(char **world) {
    if (world == NULL)
        return -1;
    else if (*world == NULL)
        return -1;
    int num;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            num = rand() % 4;
            if (num == 1) {
                world[i][j] = '1';
            } else {
                world[i][j] = '0';
            }
        }
    }

    return 0;
}

/**
 * Run the game using SDL2 to show the graphical interface
 * Users can specify the steps of iterations by entering a number, or do not specify the steps by entering a letter "q"
 * Users can enter the key "SPACE" to begin or pause the game, and the key "UP"/"DOWN" to speed up/slow down the game
 *
 * For example:
 * game("game1.txt", world)
 * returns nothing
 *
 * @param fileName the name of the file which is the second parameter in the terminal.
 * @param world a 2-dimensional array which stores the live states of cells.
 * @return 0 if run successfully, otherwise -1;
 */
int game(char *fileName, char **world) {
    if (fileName == NULL || world == NULL) {
        return -1;
    } else if (*world == NULL) {
        return -1;
    }
    char *evolveNumberString = (char *) malloc(sizeof(char) * 120);
    printf("\n----- Welcome to game of life! -----\n");
    printf("\n[1] Enter 'SPACE' to pause or continue(begin);\n");
    printf("[2] Enter 'UP' to speed up the evolving;\n");
    printf("[3] Enter 'DOWN' to slow down the evolving;\n");
    printf("[4] Enter 'c' to clear the screen;\n");
    printf("[5] Enter 'r' to randomly generate a new world;\n");
    printf("[6] Enter 'RIGHT' to the next generation;\n");
    printf("[7] Enter 'ESC' to quit.\n");
    printf("\nPlease enter the number of steps to evolve\n(enter the letter 'q' means not to specify the number)\n->");
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

    bool quit = false;

    SDL_Event e;
    int steps = 0;
    int leftEvolve = specifyEvolve;
    char **newWorld = NULL;
    int flag = 1;
    int tag = 1;
    int delayDuration = 50;
    int buttonDown = 0;
    int x, y, i, j, new_i, new_j;
    int statement_tag = 1;
    bool pause = true;
    while (!quit) {
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (SDL_BUTTON_LEFT == e.button.button) {
                        x = e.button.x;
                        y = e.button.y;
                        i = y / unitLength;
                        j = x / unitLength;
                        if (world[i][j] == '0') {
                            world[i][j] = '1';
                        } else {
                            world[i][j] = '0';
                        }
                        drawWorld(world, row, column, unitLength);
                        buttonDown = 1;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (buttonDown == 1) {
                        x = e.motion.x;
                        y = e.motion.y;
                        new_i = y / unitLength;
                        new_j = x / unitLength;
                        if (new_i != i || new_j != j) {
                            if (world[new_i][new_j] == '0') {
                                world[new_i][new_j] = '1';
                            } else {
                                world[new_i][new_j] = '0';
                            }
                        }
                        i = new_i;
                        j = new_j;
                        drawWorld(world, row, column, unitLength);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (SDL_BUTTON_LEFT == e.button.button) {
                        buttonDown = 0;
                    }
                    break;
                case SDL_QUIT:
                    freeWorld(newWorld);
                    closeSDL();
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_SPACE:
                            if (pause == true) {
                                pause = false;
                            } else {
                                pause = true;
                            }
                            break;
                        case SDLK_UP:
                            if (delayDuration >= 100 && delayDuration <= 600) {
                                delayDuration -= 50;
                                printf("Current delay duration: %d\n", delayDuration);
                            }
                            break;
                        case SDLK_DOWN:
                            if (delayDuration >= 50 && delayDuration <= 550) {
                                delayDuration += 50;
                                printf("Current delay duration: %d\n", delayDuration);
                            }
                            break;
                        case SDLK_ESCAPE:
                            freeWorld(newWorld);
                            closeSDL();
                            quit = true;
                            break;
                        case SDLK_c:
                            if (pause == 1) {
                                clearScreen(world);
                                drawWorld(world, row, column, unitLength);
                            }
                            break;
                        case SDLK_r:
                            if (pause == 1) {
                                randomScreen(world);
                                drawWorld(world, row, column, unitLength);
                            }
                            break;
                        case SDLK_RIGHT:
                            if (pause == 1 && (leftEvolve > 0 || leftEvolve == -1)) {
                                world = nextGeneration(world);
                                newWorld = nextGeneration(world);
                                steps++;
                                if (leftEvolve != -1)
                                    leftEvolve--;
                                drawWorld(world, row, column, unitLength);
                                if (compareWorld(world, newWorld, row, column)) {
                                    printf("A total of %d rounds of cell evolution is stabilized.\n", steps);
                                    freeWorld(newWorld);
                                    while (SDL_WaitEvent(&e)) {
                                        switch (e.type) {
                                            case SDL_QUIT:
                                                closeSDL();
                                                tag = 0;
                                                quit = true;
                                                break;
                                            case SDL_KEYDOWN:
                                                switch (e.key.keysym.sym) {
                                                    case SDLK_ESCAPE:
                                                        closeSDL();
                                                        tag = 0;
                                                        quit = true;
                                                        break;
                                                }
                                            default:
                                                break;
                                        }
                                    }
                                    quit = true;
                                }
                                if (leftEvolve == 0) {
                                    printf("According to the requirements, a total of %d iterations were made.\n",
                                           specifyEvolve);
                                    statement_tag = 0;
                                }
                            }
                            break;
                    }
                    break;
                default:
                    if (flag == 1) {
                        drawWorld(world, row, column, unitLength);
                        flag = 0;
                    }
                    break;
            }
        } else {
            if (!pause) {
                if (specifyEvolve == -1) {
                    newWorld = nextGeneration(world);
                    if (compareWorld(world, newWorld, row, column)) {
                        printf("A total of %d rounds of cell evolution is stabilized.\n", steps);
                        freeWorld(newWorld);
                        while (SDL_WaitEvent(&e)) {
                            switch (e.type) {
                                case SDL_QUIT:
                                    closeSDL();
                                    tag = 0;
                                    quit = true;
                                    break;
                                case SDL_KEYDOWN:
                                    switch (e.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                            closeSDL();
                                            tag = 0;
                                            quit = true;
                                            break;
                                    }
                                default:
                                    break;
                            }
                        }
                    }
                    if (tag == 1) {
                        freeWorld(world);
                        world = newWorld;
                        newWorld = NULL;
                        SDL_Delay(delayDuration);
                        drawWorld(world, row, column, unitLength);
                    }
                    steps++;
                } else {
                    newWorld = nextGeneration(world);
                    if (compareWorld(world, newWorld, row, column)) {
                        printf("A total of %d rounds of cell evolution is stabilized.\n", steps);
                        freeWorld(newWorld);
                        while (SDL_WaitEvent(&e)) {
                            switch (e.type) {
                                case SDL_QUIT:
                                    closeSDL();
                                    tag = 0;
                                    quit = true;
                                    break;
                                case SDL_KEYDOWN:
                                    switch (e.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                            closeSDL();
                                            tag = 0;
                                            quit = true;
                                            break;
                                    }
                                default:
                                    break;
                            }
                        }
                    } else if (leftEvolve == 0) {
                        if (statement_tag == 1)
                            printf("According to the requirements, a total of %d iterations were made.\n",
                                   specifyEvolve);
                        freeWorld(newWorld);
                        while (SDL_WaitEvent(&e)) {
                            switch (e.type) {
                                case SDL_QUIT:
                                    closeSDL();
                                    tag = 0;
                                    quit = true;
                                    break;
                                case SDL_KEYDOWN:
                                    switch (e.key.keysym.sym) {
                                        case SDLK_ESCAPE:
                                            closeSDL();
                                            tag = 0;
                                            quit = true;
                                            break;
                                    }
                                default:
                                    break;
                            }
                        }
                    }
                    if (tag == 1) {
                        freeWorld(world);
                        world = newWorld;
                        newWorld = NULL;
                        SDL_Delay(delayDuration);
                        drawWorld(world, row, column, unitLength);
                    }
                    steps++;
                    leftEvolve--;
                }
            }
        }
    }

    storeWorld(fileName, world, row, column);
    freeWorld(world);

    free(evolveNumberString);
    evolveNumberString = NULL;

    return 0;
}