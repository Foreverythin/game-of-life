#ifndef GAME_OF_LIFE_GAME_H
#define GAME_OF_LIFE_GAME_H
extern int row, column;

void game(char** world);

char** nextGeneration(char** world);
#endif //GAME_OF_LIFE_GAME_H
