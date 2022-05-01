#include <string.h>
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