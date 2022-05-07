#ifndef GAME_OF_LIFE_FILEIO_H
#define GAME_OF_LIFE_FILEIO_H

char **readWorld(char *fileName, unsigned int row, unsigned int column);

void storeWorld(char* fileName, char** world, unsigned int row, unsigned int column);

#endif //GAME_OF_LIFE_FILEIO_H
