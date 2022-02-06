#ifndef DICTIONARY_H
#define DICTIONARY_H

// Introduce the FILE struct for serialization.
#include <stdio.h>

// A dictionary that lets us retrieve arbitrary
// void * data using a string identifier. Useful
// in general, but mainly for serialization.
// Implementd as a binary search tree.
// An empty dictionary is represented as NULL.
typedef struct Dictionary{
    // The string identifier.
    const char *key;

    // The pointer to the data.
    void *data;

    // The left and right children.
    struct Dictionary *left, *right;
} T_DICTIONARY;

// Insert (or replace) the value at the key.
// If a value gets replaced it is returned for the caller to
// discard it as needed.
void *DictionaryInsert(T_DICTIONARY **dictionary, const char *key, void *data);

// Finds the node that matches the given key the closest and returns it.
// Useful for entering shortened commands. Still returns NULL
// for an empty dictionary though.
T_DICTIONARY *DictionarySearch(T_DICTIONARY **dictionary, const char *key);

// Find the give key and return the associated data or NULL if not found.
void *DictionaryGet(T_DICTIONARY **dictionary, const char *key);

// Similar to Get but the corresponding node gets deleted.
// It is the responsibility of the caller to dispose of the data.
void *DictionaryRemove(T_DICTIONARY **dictionary, const char *key);

// Similar to Remove, but the key is undefined. Removes nothing from
// an empty instance and returns NULL in that case. This can be called
// repeatedly until NULL is returned to clear the dictionary. A simple
// clear method wouldn't work as the data cannot always be just freed.
void *DictionaryRemoveSomething(T_DICTIONARY **dictionary);

// Construct a dictionary from an input stream (when loading a game).
T_DICTIONARY *DictionaryDeserialize(FILE *source);

// Store a dictionary to an output stream (when saving a game).
void *DictionarySerialize(FILE *destination);

// Ballance the tree to optimize the speed of subsequent searches.
// Useful for mostly immutable dictionaries that are searched
// frequently as it is too slow to be performed regularly.
// NOTE: did't realize this at first, but really large datasests
// benefit from multiple optimizations during the population itself.
// An example that works with most linux installs should be the state
// at tag v0.0.1
void DictionaryOptimize(T_DICTIONARY **dictionary);

#endif // DICTIONARY_H