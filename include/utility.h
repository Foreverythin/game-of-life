#ifndef GAME_OF_LIFE_UTILITY_H
#define GAME_OF_LIFE_UTILITY_H
bool isNumber(char* s);

/**
 * row is the number of rows in the world which is in the interval of [0, 65535]
 * column is the number of columns in the world which is also in the interval of [0, 65535]
 */
unsigned int row, column;

/**
 * unitLength is the width of each small cell square, computed by 640.0/max(row, column)
 */
float unitLength;

#endif //GAME_OF_LIFE_UTILITY_H
