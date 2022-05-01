#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/utility.h"

char** nextGeneration(char** world){
    return (char **) world;
}

void game(char** world) {
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
    char *evolveNumberString = (char *) malloc(sizeof(char));
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

    char** worl = nextGeneration(world);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", worl[i][j]);
            if (j == column - 1) {
                printf("\n");
            }
        }
    }
}