#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/utility.h"

void freeWorld(char **world) {
    for (int i = 0; i < row; i++) {
        free(world[i]);
    }
    free(world);
    world = NULL;
}

int compareWorld(char **world, char **newWorld) {
    int numEqual = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (world[i][j] == newWorld[i][j]) {
                numEqual++;
            }
        }
    }
    if (numEqual == (row * column)) {
        return 1;
    } else {
        return 0;
    }
}

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
    char *evolveNumberString = (char *) malloc(sizeof(char) * 120);
    printf("Please enter the number of steps to evolve\n(enter the letter 'q' means not to specify the number)\n->");
    gets(evolveNumberString);
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

    if (specifyEvolve == -1) {
        int steps = 0;
        while (1) {
            char **newWorld = nextGeneration(world);
            printf("\n");
            if (compareWorld(world, newWorld) == 1) {
                printf("A total of %d rounds of cell evolution is stabilized", steps);
                freeWorld(newWorld);
                break;
            }
            freeWorld(world);
            world = newWorld;
            newWorld = NULL;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    printf("%c ", world[i][j]);
                    if (j == column - 1) {
                        printf("\n");
                    }
                }
            }
            steps++;
        }
    }else{
        int steps = 0;
        int leftEvolve = specifyEvolve;
        while (leftEvolve > 0){
            char **newWorld = nextGeneration(world);
            printf("\n");
            if (compareWorld(world, newWorld) == 1) {
                printf("A total of %d rounds of cell evolution is stabilized", steps);
                freeWorld(newWorld);
                break;
            }
            freeWorld(world);
            world = newWorld;
            newWorld = NULL;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    printf("%c ", world[i][j]);
                    if (j == column - 1) {
                        printf("\n");
                    }
                }
            }
            steps++;
            leftEvolve--;
        }
        printf("按照要求，一共迭代了%d次。", specifyEvolve);
    }
    
    freeWorld(world);
    free(evolveNumberString);
    evolveNumberString = NULL;

}