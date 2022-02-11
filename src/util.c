#include <stdlib.h>

#include "util.h"

char *simpleGetLine(FILE *stream){
    char *result = NULL;
    size_t n = 0;
    int res = getline(&result, &n, stream);
    if(res == -1){
        free(result);
        result = NULL;
    }
    if(result && result[res - 1] == '\n')
        result[res - 1] = '\0';
    return result;
}