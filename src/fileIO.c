#include <stdio.h>
#include <stdlib.h>
#include "../include/fileIO.h"

//char *readWorld(char *fileName, int row, int column) {
//    char* world = (char *) malloc(sizeof(char) * (row * column));
//    FILE *file = fopen(fileName, "r");
//    fscanf(file, "%d %d\n", &row, &column);
//    for (int i = 0; i < row * column; i++) {
//        world[i] = fgetc(file);
//        fgetc(file);
//    }
//    fclose(file);
//    return world;
//}
char **readWorld(char *fileName, int row, int column) {
    char **world = (char **) malloc(sizeof(char *)*row);
    for (int i = 0; i < row; i ++){
        world[i] = (char*) malloc(sizeof(char*)*column);
    }
    FILE *file = fopen(fileName, "r");
    fscanf(file, "%d %d\n", &row, &column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++){
            world[i][j] = fgetc(file);
            fgetc(file);
        }
    }
    fclose(file);
    return world;
}

