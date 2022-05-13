#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/utility.h"

/**
 * judge whether the string s can be converted to int
 *
 * For example:
 * isNumber("234a")
 * returns false
 *
 * isNumber("123")
 * returns true
 *
 * @param s a string which will be judged
 * @return true if the string s can be converted to int
 *         otherwise false
 */
bool isNumber(char* s){
    if (s == NULL){
        return false;
    }
    if (strlen(s) == 0){
        return false;
    }
    if (strspn(s, "0123456789")==strlen(s)){
        return true;
    }else{
        return false;
    }
}
