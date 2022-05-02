#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/utility.h"

// judge whether the string s can be converted to int
// if can, return 1
// else, return 0
bool isNumber(char* s){
    if (strspn(s, "0123456789")==strlen(s)){
        return true;
    }else{
        return false;
    }
}
