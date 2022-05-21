#ifndef GAME_OF_LIFE_GAME_H
#define GAME_OF_LIFE_GAME_H
#include <stdbool.h>
extern unsigned int row, column;
extern float unitLength;

int clearScreen(char** world);

int randomScreen(char** world);

void freeWorld(char** world);

//if 2 worlds are exactly same, return 1; otherwise 0.
bool compareWorld(char** world, char** newWorld, unsigned int row, unsigned int column);

void game(char* fileName, char** world);

char** nextGeneration(char** world);
#endif //GAME_OF_LIFE_GAME_H
