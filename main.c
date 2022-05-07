#include <stdio.h>
#include "include/fileIO.h"
#include "include/game.h"
#include "include/interface.h"

/**
 * row is the number of rows in the world which is in the interval of [0, 65535]
 * column is the number of columns in the world which is also in the interval of [0, 65535]
 */
unsigned int row, column;

/**
 * unitLength is the width of each small cell square, computed by 640.0/max(row, column)
 */
float unitLength;

/**
 * The entrance function of this game - "game of life"
 *
 * To run this game, for example:
 * "./GameOfLife game1.txt"
 * returns 0
 *
 * @param argc the number of parameters users entered in the terminal
 *      the value of argc must be 2. Otherwise the program will report error and finish.
 * @param argv a string array which stores the parameters users entered in the terminal
 *      the first parameter must be "./GameOfLife"
 *      the second parameter must be a file's name which exists in the bin directory and records the state of cells
 *      if the file doesn't exist, then the program will report error and finish.
 * @return return 0 if the parameters are correct and SDL, SDL_image are initialized with no error
 *         return -1 if the parameters are wrong or SDL, SDL_image are initialized with error
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error!\nExpected use: ./GameOfLife <*.txt>");
        return -1;
    } else {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Error!\nNo such file called %s!", argv[1]);
            return -1;
        } else {
            fscanf(file, "%u %u", &row, &column);
            unitLength = (640.0f/(float)row>640.0f/(float)column)?(640.0f/(float)column):(640.0f/(float)row);
            fclose(file);
        }
    }

    char **world = readWorld(argv[1], row, column);

    if (init()){
        game(argv[1], world);
    }else{
        freeWorld(world);
        closeSDL();
        return -1;
    }

    closeSDL();

    return 0;
}
