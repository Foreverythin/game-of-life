#include <stdio.h>
#include <SDL2/SDL.H>
#include "include/fileIO.h"
#include "include/game.h"

int row, column;

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
            fclose(file);
        }
    }
    char **world = readWorld(argv[1], row, column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", world[i][j]);
            if (j == column - 1) {
                printf("\n");
            }
        }
    }

    game(world);
//    for (int i = 0; i < row; i++){
//        free(world[i]);
//    }
//    free(world);

    return 0;
}
