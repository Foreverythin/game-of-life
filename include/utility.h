#ifndef GAME_OF_LIFE_UTILITY_H
#define GAME_OF_LIFE_UTILITY_H
int isNumber(char* s);

extern int row, column;

void freeWorld(char** world);

void copyWorld(char** world, char** newWorld);
#endif //GAME_OF_LIFE_UTILITY_H
