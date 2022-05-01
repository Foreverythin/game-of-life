#include <string.h>
#include <stdlib.h>
#include "../include/utility.h"

// judge whether the string s can be converted to int
// if can, return 1
// else, return 0
int isNumber(char* s){
    if (strspn(s, "0123456789")==strlen(s)){
        return 1;
    }else{
        return 0;
    }
}

void freeWorld(char** world){
    for (int i = 0; i < row; i++){
        free(world[i]);
    }
    free(world);
}

void copyWorld(char** world, char** newWorld){
    for (int i = 0; i < row; i ++){
        world[i] = newWorld[i];
    }
    world = newWorld;
}