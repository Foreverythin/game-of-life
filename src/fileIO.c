#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fileIO.h"

/**
 * read the file which exists in the bin directory and records the state of cells,
 * and store the information into a temporary 2-dimensional array.
 *
 * For example:
 * readWorld("game1.txt", row, column)
 * returns world
 *
 * @param fileName which is the file's name, which exists in the bin directory and records the live states of cells.
 * @param row is the number of rows in the world which is in the interval of [0, 65535]
 * @param column is the number of columns in the world which is in the interval of [0, 65535]
 *
 * @return a 2-dimensional array which contains the information of live states of cells
 */
char **readWorld(char *fileName, unsigned int row, unsigned int column) {
    char **world = (char **) malloc(sizeof(char *) * row);
    for (int i = 0; i < row; i++) {
        world[i] = (char *) malloc(sizeof(char) * column);
    }
    FILE *file = fopen(fileName, "r");
    fscanf(file, "%u %u\n", &row, &column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            world[i][j] = fgetc(file);
            fgetc(file);
        }
    }
    fclose(file);
    return world;
}

/**
 * store the 2-dimensional array "world" which stores the live states of cells to a file.
 *
 * For example:
 * storeWorld("game1.txt", world, row, column)
 * returns nothing
 *
 * @param fileName is the name of the file which is the second parameter in the terminal.
 * @param world is a 2-dimensional array which stores the live states of cells.
 * @param row is the number of rows in the world which is in the interval of [0, 65535]
 * @param column is the number of columns in the world which is in the interval of [0, 65535]
 *
 * @return nothing
 */
void storeWorld(char *fileName, char **world, unsigned int row, unsigned int column) {
    char src[50], dest[50];

    strcpy(dest, "output_");
    strcpy(src, fileName);

    strcat(dest, src);
    FILE *file = fopen(dest, "w");
    if (!file) {
        printf("Wrong to store last generation's information to the file!\n");
    } else {
        fprintf(file, "%u %u\n", row, column);
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
