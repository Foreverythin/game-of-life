#include <stdio.h>
#include <SDL2/SDL.h>
#include "include/fileIO.h"
#include "include/game.h"
#include "include/interface.h"


int row, column;
float unitLength;

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
            fscanf(file, "%d %d", &row, &column);
            unitLength = (640.0f/(float)row>640.0f/(float)column)?(640.0f/(float)column):(640.0f/(float)row);
            fclose(file);
        }
    }
    char **world = readWorld(argv[1], row, column);
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < column; j++) {
//            printf("%c ", world[i][j]);
//            if (j == column - 1) {
//                printf("\n");
//            }
//        }
//    }

    if (init()){
        game(world);
    }else{
        freeWorld(world);
    }


    return 0;
}
