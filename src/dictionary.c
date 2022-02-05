#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Check which string has more matching characters. Useful for
// the search function. Can stay inside this file.
const char *getCloserString(const char *target, const char *a, const char *b){
    int i;
    for(i = 0; target[i]; i++){
        if(a[i] != target[i] && b[i] != target[i]){
            int da = a[i] - target[i] >= 0 ? a[i] - target[i] : target[i] - a[i];
            int db = b[i] - target[i] >= 0 ? b[i] - target[i] : target[i] - b[i];
            return da < db ? a : b;
        }

        if(a[i] != target[i])
            return b;

        if(b[i] != target[i])
            return a;

        // Being different includes ending sooner, because '\0' will never
        // be the same as any character inside target.
    }

    // If they were the same up to this point, return either the one that
    // is the same as the target or b (doesn't matter in that case).
    return a[i] ? b : a;
}

T_DICTIONARY *DictionarySearch(T_DICTIONARY **dictionary, const char *key){
    if(!*dictionary) // There is nothing to find in an empty dictionary
        return NULL;

    int cmp = strcmp(key, (*dictionary)->key);

    if(cmp == 0) // We have just found it.
        return *dictionary;

    if(cmp < 0){ // What we are looking for is less than what we have
        if((*dictionary)->left){ // We have something smaller
            T_DICTIONARY *left = DictionarySearch(&(*dictionary)->left, key);
            return // Return the closer one.
                getCloserString(key, left->key, (*dictionary)->key) == left->key ?
                left : *dictionary;
        }else{
            // If there is nothing to the left...
            return *dictionary;
        }
    }

    if(cmp > 0){ //Similar as before
        if((*dictionary)->right){
            T_DICTIONARY *right = DictionarySearch(&(*dictionary)->right, key);
            return
                getCloserString(key, right->key, (*dictionary)->key) == right->key ?
                right : *dictionary;
        }else{
            return *dictionary;
        }
    }

    return NULL; // For the warnings (I want the ifs to look the way they do)
}

void *DictionaryInsert(T_DICTIONARY **dictionary, const char *key, void *data){
    // A recursive approach is chosen for ease of implementation

    // If we have arrived at NULL, the key is definitely not to be found.
    if(!(*dictionary)){
        *dictionary = malloc(sizeof(T_DICTIONARY));
        (*dictionary)->data = data;
        (*dictionary)->key = key;
        (*dictionary)->left = (*dictionary)->right = NULL;
        return NULL;
    }

    // Else we check the current key
    int cmp = strcmp(key, (*dictionary)->key);

    // We could have found it
    if(cmp == 0){
        // Save the value first, so the caller can safely dispose of the data.
        void *result = (*dictionary)->data;
        (*dictionary)->data = data;
        return result;
    }

    if(cmp < 0) // It is in the left subtree, or at least belongs there
        return DictionaryInsert(&(*dictionary)->left, key, data);

    if(cmp > 0) // It is in the right subtree, or at least belongs there
        return DictionaryInsert(&(*dictionary)->right, key, data);

    return NULL; // For the warnings (I want the ifs to look the way they do)
}

void DictionaryOptimize(T_DICTIONARY **dictionary){

}
