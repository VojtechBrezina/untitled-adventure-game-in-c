#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// A dynamically growing array implemented for arbitrary data.
// The numbers 4 and 2 are taken from the .NET implementation
// because I just cannot not let you know, that I remember
// things like that. (correctly I hope)
typedef struct{
    int size;
    int capacity;
    void **data;
} T_DYNAMIC_ARRAY;

// Initialize an empty instance.
void DynamicArrayInit(T_DYNAMIC_ARRAY *array);

// Append a given value as the last element.
void DynamicArrayAppend(T_DYNAMIC_ARRAY *array, void *value);

// Remove an element from the array and return it to the user.
// To dispose of it as necessary.
void *DynamicArrayRemove(T_DYNAMIC_ARRAY *array, int index);

// Remove the element by overwriting it with the last one and
// decreasing the size. O(1), but disturbs the order of elements.
void *DynamicArrayFastRemove(T_DYNAMIC_ARRAY *array, int index);

// This function ensures all memory is returned and puts the array
// in an invalid state. Not to be confused with clearing the array
// which has to be performed manually as the arbitrary nature of the
// data doesn't make anything more efficient possible. It is assumed
// the data has already been destroyed by the caller.
void DynamicArrayDone(T_DYNAMIC_ARRAY *array);

#endif // DYNAMIC_ARRAY_H