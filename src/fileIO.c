#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileIO.h"

char **readWorld(char *fileName, int row, int column) {
    char **world = (char **) malloc(sizeof(char *) * row);
    for (int i = 0; i < row; i++) {
        world[i] = (char *) malloc(sizeof(char) * column);
    }
    FILE *file = fopen(fileName, "r");
    fscanf(file, "%d %d\n", &row, &column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            world[i][j] = fgetc(file);
            fgetc(file);
        }
    }
    fclose(file);
    return world;
}

void storeWorld(char *fileName, char **world, int row, int column) {
    char src[50], dest[50];

    strcpy(dest, "output_");
    strcpy(src, fileName);

    strcat(dest, src);
    FILE *file = fopen(dest, "w");
    if (!file) {
        printf("Wrong to store last generation's information to the file!\n");
    } else {
        fprintf(file, "%d %d\n", row, column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                fputc(world[i][j], file);
                if (j != (column - 1)) {
                    fprintf(file, " ");
                }
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Successfully store last generation's information to the file: %s\n", dest);
    }
}
