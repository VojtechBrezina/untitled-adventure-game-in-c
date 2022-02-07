#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Used in the optimization code.
#include "dynamic_array.h"

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
        (*dictionary)->key = strdup(key);
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

void **DictionaryGet(T_DICTIONARY **dictionary, const char *key){
    // Once again recursion will be the nicer way. It is similar
    // to the insert function, but no new node can be created
    // this way.
    if(!*dictionary)
        return NULL;

    int cmp = strcmp(key, (*dictionary)->key);

    if(cmp == 0)
        return &(*dictionary)->data;

    if(cmp < 0)
        return DictionaryGet(&(*dictionary)->left, key);

    if(cmp > 0)
        return DictionaryGet(&(*dictionary)->right, key);

    return NULL; // For the warnings (I want the ifs to look the way they do)
}

// A recursive helper function for the first step of optimization.
void constructInOrderArray(T_DICTIONARY *dictionary, T_DYNAMIC_ARRAY *target){
    if(!dictionary)
        return;

    constructInOrderArray(dictionary->left, target);
    DynamicArrayAppend(target, dictionary);
    constructInOrderArray(dictionary->right, target);
}

// A helper function for the second optimization step
T_DICTIONARY *rebuildDictionary(T_DYNAMIC_ARRAY *source, int first, int last){
    // If the indexes cross, stop the recursion
    if(last < first)
        return NULL;

    // Make the middle one the root to ensure the same ammount of nodes
    // on both sides, then rebuild the subtrees.
    int middle = first + (last - first) / 2;
    T_DICTIONARY *result = source->data[middle];
    result->left = rebuildDictionary(source, first, middle - 1);
    result->right = rebuildDictionary(source, middle + 1, last);
    return result;
}

void DictionaryOptimize(T_DICTIONARY **dictionary){
    // If it is empty, it is plenty optimized
    // (and could break at least step 2)
    if(!*dictionary)
        return;

    T_DYNAMIC_ARRAY inOrderArray;
    DynamicArrayInit(&inOrderArray);

    // Step 1: get an ordered array of the nodes
    constructInOrderArray(*dictionary, &inOrderArray);

    // Step 2: reorganize the nodes optimaly
    *dictionary = rebuildDictionary(&inOrderArray, 0, inOrderArray.size - 1);

    DynamicArrayDone(&inOrderArray);
}

void *DictionaryRemove(T_DICTIONARY **dictionary, const char *key){
    // Still technically fits into one screen :) (on my device that is)
    // EDIT: Ok, It is a mess, but I swear it will be an exception.
    if(!*dictionary)
        return NULL;

    int cmp = strcmp(key, (*dictionary)->key);

    if(cmp == 0){
        void *result = (*dictionary)->data;
        // Type cast to remove const, not sure about this...
        free((char *)(*dictionary)->key);
        T_DICTIONARY *left = (*dictionary)->left;
        T_DICTIONARY *right = (*dictionary)->right;
        free(*dictionary);
        // If they are both NULL, it will be set to right, that is to NULL.
        if(left){
            *dictionary = right;
        }else if(right){
            *dictionary = left;
        }else{
            T_DICTIONARY *what, **where;
            if(key[0] % 2){ // Trying to make it at least somewhat balanced
                what = right;
                *dictionary = left;
                for(where = &right; *where; where = &(*where)->right);
            }else{
                what = left;
                *dictionary = right;
                for(where = &left; *where; where = &(*where)->left);
            }
            *where = what;
        }
        return result;
    }

    if(cmp < 0)
        return DictionaryRemove(&(*dictionary)->left, key);
    if(cmp > 0)
        return DictionaryRemove(&(*dictionary)->right, key);
    return NULL; // For the warnings (I want the ifs to look the way they do)
}

// The actual implementation needs to differentiate between success
// and failure.
int removeSomethingImpl(T_DICTIONARY **dictionary, void **value){
    if(!(*dictionary))
        return 0;

    if(removeSomethingImpl(&(*dictionary)->left, value))
        return 1;

    if(removeSomethingImpl(&(*dictionary)->right, value))
        return 1;

    *value = (*dictionary)->data;
    free((char *)(*dictionary)->key);
    free(*dictionary);
    *dictionary = NULL;
    return 1;
}

void *DictionaryRemoveSomething(T_DICTIONARY **dictionary){
    void *result = NULL;
    removeSomethingImpl(dictionary, &result);
    return result;
}
