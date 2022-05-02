#ifndef GAME_OF_LIFE_GAME_H
#define GAME_OF_LIFE_GAME_H
extern int row, column;

void freeWorld(char** world);

//if 2 worlds are exactly same, return 1; otherwise 0.
int compareWorld(char** world, char** newWorld);

void game(char** world);

char** nextGeneration(char** world);
#endif //GAME_OF_LIFE_GAME_H
