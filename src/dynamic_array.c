#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dynamic_array.h"

void DynamicArrayInit(T_DYNAMIC_ARRAY *array){
    array->size = 0;
    array->capacity = 4;
    array->data = malloc(sizeof(void *) * array->capacity);
}

void DynamicArrayAppend(T_DYNAMIC_ARRAY *array, void *value){
    // If in debug mode, ensure the array hasn't been disposed.
    assert(array->capacity != 0);

    if(array->size == array->capacity){
        array->capacity *= 2;
        array->data = realloc(array->data, sizeof(void *) * array->capacity);
    }

    array->data[array->size++] = value;
}

void *DynamicArrayRemove(T_DYNAMIC_ARRAY *array, int index){
    // Basic integrity checks:
    assert(index < array->size && index >= 0);

    void *value = array->data[index];
    memmove(array->data + index, array->data + index - 1, array->size - index - 1);
    array->size--;
    return value;
}

void *DynamicArrayFastRemove(T_DYNAMIC_ARRAY *array, int index){
    // Basic integrity checks:
    assert(index < array->size && index >= 0);

    void *value = array->data[index];
    array->data[index] = array->data[--(array->size)];
    return value;
}

void DynamicArrayDone(T_DYNAMIC_ARRAY *array){
    free(array->data);
    array->data = NULL;
    array->size = array->capacity = 0;
}
