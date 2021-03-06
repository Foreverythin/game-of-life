#include "../include/CUnit/CUnit.h"
#include "../include/CUnit/Basic.h"
#include <stdlib.h>
#include "../include/fileIO.h"
#include "../include/game.h"
#include "../include/interface.h"
#include "../include/utility.h"


void test_readWorld() {
    CU_ASSERT_PTR_NULL(readWorld(NULL, 0, 0));
    CU_ASSERT_PTR_NULL(readWorld(NULL, 32, 0));
    CU_ASSERT_PTR_NULL(readWorld("Game.txt", 32, 32));
    CU_ASSERT_PTR_NULL(readWorld("game1.txt", 32, 0));
    CU_ASSERT_PTR_NOT_NULL(readWorld("game1.txt", 32, 32));
}

// test the function of storeWorld in fileIO.h
void test_storeWorld() {
    // a new 2-dimensional array
    char **world = (char **) malloc(sizeof(char *) * 32);
    for (int i = 0; i < 32; i++) {
        world[i] = (char *) malloc(sizeof(char) * 32);
    }
    CU_ASSERT_EQUAL(storeWorld(NULL, NULL, 0, 0), 0);
    CU_ASSERT_EQUAL(storeWorld(NULL, NULL, 32, 32), 0);
    CU_ASSERT_EQUAL(storeWorld(NULL, world, 32, 32), 0);
    CU_ASSERT_EQUAL(storeWorld("game1.txt", NULL, 32, 32), 0);
    CU_ASSERT_EQUAL(storeWorld("game1.txt", world, 32, 32), 1);

    // free the pointer
    for (int i = 0; i < 32; i++) {
        free(world[i]);
        world[i] = NULL;
    }
    free(world);
    world = NULL;
}

// test the function of compareWorld in game.h
void test_compareWorld() {
    // two new 2-dimensional arrays
    char **world = (char **) malloc(sizeof(char *) * 32);
    for (int i = 0; i < 32; i++) {
        world[i] = (char *) malloc(sizeof(char) * 32);
    }
    char **newWorld = (char **) malloc(sizeof(char *) * 32);
    for (int i = 0; i < 32; i++) {
        newWorld[i] = (char *) malloc(sizeof(char) * 32);
    }
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            world[i][j] = '1';
            newWorld[i][j] = '1';
        }
    }
    CU_ASSERT_EQUAL(compareWorld(NULL, NULL, 0, 0), CU_FALSE);
    CU_ASSERT_EQUAL(compareWorld(world, newWorld, 0, 0), CU_FALSE);
    CU_ASSERT_EQUAL(compareWorld(world, newWorld, 32, 32), CU_TRUE);
    CU_ASSERT_EQUAL(compareWorld(NULL, NULL, 32, 32), CU_FALSE);
    CU_ASSERT_EQUAL(compareWorld(world, NULL, 32, 32), CU_FALSE);
    CU_ASSERT_EQUAL(compareWorld(NULL, newWorld, 32, 32), CU_FALSE);

    newWorld[0][0] = '0';
    CU_ASSERT_EQUAL(compareWorld(world, newWorld, 0, 0), CU_FALSE);
    CU_ASSERT_EQUAL(compareWorld(world, newWorld, 32, 32), CU_FALSE);

    // free the pointers
    for (int i = 0; i < 32; i++) {
        free(world[i]);
        world[i] = NULL;
        free(newWorld[i]);
        newWorld[i] = NULL;
    }
    free(world);
    world = NULL;
    free(newWorld);
    newWorld = NULL;
}

// test the function of compareWorld in game.h
void test_nextGeneration(){
    // two new 2-dimensional arrays
    char **world = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        world[i] = (char *) malloc(sizeof(char) * 3);
    }
    char **newWorld = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        newWorld[i] = (char *) malloc(sizeof(char) * 3);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            world[i][j] = '1';
            newWorld[i][j] = '1';
        }
    }
    CU_ASSERT_EQUAL(nextGeneration(NULL), NULL);
    CU_ASSERT_NOT_EQUAL(nextGeneration(world), newWorld);

    // free the pointers
    for (int i = 0; i < 3; i++) {
        free(world[i]);
        world[i] = NULL;
        free(newWorld[i]);
        newWorld[i] = NULL;
    }
    free(world);
    world = NULL;
    free(newWorld);
    newWorld = NULL;
}

//test the function of isNumber
void test_isNumber(){
    CU_ASSERT_TRUE(isNumber("1124"));
    CU_ASSERT_TRUE(isNumber("0"));
    CU_ASSERT_FALSE(isNumber("-1"));
    CU_ASSERT_FALSE(isNumber("a"));
    CU_ASSERT_FALSE(isNumber("apple123"));
    CU_ASSERT_FALSE(isNumber(""));
    CU_ASSERT_FALSE(isNumber(NULL));
}

//test the function of clearScreen
void test_clearScreen(){
    // two new 2-dimensional arrays
    char **world = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        world[i] = (char *) malloc(sizeof(char) * 3);
    }

    CU_ASSERT_EQUAL(clearScreen(world), 0);

    for (int i = 0; i < 3; i++) {
        free(world[i]);
        world[i] = NULL;
    }

    CU_ASSERT_EQUAL(clearScreen(world), -1);

    free(world);
    world = NULL;

    CU_ASSERT_EQUAL(clearScreen(world), -1);
    CU_ASSERT_EQUAL(clearScreen(NULL), -1);
}

// test the function of randomScreen
void test_randomScreen(){
    // two new 2-dimensional arrays
    char **world = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        world[i] = (char *) malloc(sizeof(char) * 3);
    }

    CU_ASSERT_EQUAL(randomScreen(world), 0);

    for (int i = 0; i < 3; i++) {
        free(world[i]);
        world[i] = NULL;
    }

    CU_ASSERT_EQUAL(randomScreen(world), -1);

    free(world);
    world = NULL;

    CU_ASSERT_EQUAL(randomScreen(world), -1);
    CU_ASSERT_EQUAL(randomScreen(NULL), -1);
}

// test the function of freeWorld
void test_freeWorld(){
    // two new 2-dimensional arrays
    char **world = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        world[i] = (char *) malloc(sizeof(char) * 3);
    }

    CU_ASSERT_EQUAL(freeWorld(world), 0);
    CU_ASSERT_EQUAL(freeWorld(NULL), -1);
}

//test the function of game
void test_game(){
    char* fileName = (char*) malloc(sizeof (char )*4);
    fileName = "test";
    char **world = (char **) malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        world[i] = (char *) malloc(sizeof(char) * 3);
    }
    CU_ASSERT_EQUAL(game(fileName, world), 0);
    CU_ASSERT_EQUAL(game(NULL, world), -1);
    CU_ASSERT_EQUAL(game(fileName, NULL), -1);
    CU_ASSERT_EQUAL(game(NULL, NULL), -1);

    free(fileName);
    fileName = NULL;
    freeWorld(world);
}

int main(void) {
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* add a suite to the registry */
    CU_pSuite pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) goto cleanup;

    /* add the tests to the suite */
    if (NULL == CU_add_test(pSuite, "test readWorld(char *fileName, unsigned int row, unsigned int column)", test_readWorld)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test storeWorld(char* fileName, char** world, unsigned int row, unsigned int column)", test_storeWorld)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test compareWorld(char** world, char** newWorld, unsigned int row, unsigned int column)", test_compareWorld)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test nextGeneration(char** world)", test_nextGeneration)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test isNumber(char* s)", test_isNumber)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test clearScreen(char** world)", test_clearScreen)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test randomScreen(char** world)", test_randomScreen)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test freeWorld(char** world)", test_freeWorld)) goto cleanup;
    if (NULL == CU_add_test(pSuite, "test game(char* fileName, char** world)", test_game)) goto cleanup;

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    cleanup:
    CU_cleanup_registry();
    return CU_get_error();
}