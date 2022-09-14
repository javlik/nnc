#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

#define FMT_RED "\033[0;31m"
#define FMT_GRN "\033[0;32m"
#define FMT_OFF "\033[0m"

/**
 * @brief rand_init
 */
void rand_init(){
    srand(time(NULL));
}

/**
 * @brief get_random_float
 * @param a
 * @return
 */
float get_random_float(float a) {
    return (float)rand()/(float)(RAND_MAX/a);
}


/**
 * @brief getShuffledIntArray
 * @param n
 * @return
 */
int* getShuffledIntArray(int n){
    int* a = (int*)malloc(n * sizeof(int));
    int i, val, tmp;

    srand(time(NULL));

    for (i=0;i<n;i++) {
        a[i]=i+1;
    }
    for (i = 0; i < n - 1; ++i) {
        val = (rand() % (n - 1 - i)) + i + 1;
        tmp = a[i];
        a[i] = a[val];
        a[val] = tmp;
    }
    return a;
}


/**
 * @brief discardShuffeldIntArray
 * @param array
 */
void discardShuffeldIntArray(int* array){
    free(array);
}


/**
 * @brief devia_print
 * @param format_string
 */
void print_deviation(const char* format_string, float f_var){
#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
    if (f_var < 0){
        printf (FMT_RED);
    } else if (f_var > 0){
        printf (FMT_GRN);
    }
#endif
    printf(format_string, f_var);
#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
    printf(FMT_OFF);
#endif
}


