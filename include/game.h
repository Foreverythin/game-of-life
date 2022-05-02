#ifndef GAME_OF_LIFE_GAME_H
#define GAME_OF_LIFE_GAME_H
#include <stdbool.h>
extern int row, column;
extern float unitLength;

void freeWorld(char** world);

//if 2 worlds are exactly same, return 1; otherwise 0.
bool compareWorld(char** world, char** newWorld);

void game(char** world);

char** nextGeneration(char** world);
#endif //GAME_OF_LIFE_GAME_H
