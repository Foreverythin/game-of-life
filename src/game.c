#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/utility.h"

char **nextGeneration(char **world) {
    char **newWorld = (char **) malloc(sizeof(char *) * row);
    for (int i = 0; i < row; i++) {
        newWorld[i] = (char *) malloc(sizeof(char *) * column);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            newWorld[i][j] = world[i][j];
        }
    }
    int num;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            num = 0;
            for (int m = -1; m < 2; m++) {
                for (int n = -1; n < 2; n++) {
                    if (!(m == 0 && n == 0)) {
                        if (i + m >= 0 && i + m < row && j + n >= 0 && j + n < column) {
                            if (world[i + m][j + n] == '1') {
                                num++;
                            }
                        }
                    }
                }
            }
            if (world[i][j] == '1') {
                if (num != 2 && num != 3) {
                    newWorld[i][j] = '0';
                }
            } else {
                if (num == 3) {
                    newWorld[i][j] = '1';
                }
            }
        }
    }
    return newWorld;
}

void game(char **world) {
    /*
     * 打印world测试二维数组正确传入函数
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", world[i][j]);
            if (j == column - 1) {
                printf("\n");
            }
        }
    }*/
    char *evolveNumberString = (char *) malloc(sizeof(char) * 10);
    printf("Please enter the number of steps to evolve\n(enter the letter 'q' means not to specify the number)\n->");
    scanf("%s", evolveNumberString);
    while (isNumber(evolveNumberString) != 1 && strcmp(evolveNumberString, "q") != 0) {
        printf("Invalid choice!\nPlease enter a number or the letter 'q':\n->");
        scanf("%s", evolveNumberString);
    }
    int specifyEvolve;
    if (strcmp(evolveNumberString, "q") == 0) {
        specifyEvolve = -1;
    } else {
        specifyEvolve = atoi(evolveNumberString);
    }

    char** newWorld = nextGeneration(world);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", newWorld[i][j]);
            if (j == column - 1) {
                printf("\n");
            }
        }
    }
    for (int i = 0; i < row; i++){
        free(world[i]);
    }
    free(world);
    for (int i = 0; i < row; i ++){
        world[i] = newWorld[i];
    }
    world = newWorld;
    printf("\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", world[i][j]);
            if (j == column - 1) {
                printf("\n");
            }
        }
    }
    for (int i = 0; i < row; i++){
        free(world[i]);
    }
    free(world);

}