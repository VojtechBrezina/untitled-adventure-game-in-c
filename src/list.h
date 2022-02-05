#ifndef LIST_H
#define LIST_H

// A double linked list node that holds arbitrary data
typedef struct ListNode{
    void *data;
    struct ListNode *next, *prev;
} T_LIST_NODE;

// A wrapper struct to hold both ends of the list
typedef struct{
    T_LIST_NODE *head, *tail;
} T_LIST;

// Set up an empty list
void ListInit(T_LIST *list);

// Index the list for read/write access. Supports python
// like negative indexing to make at least some use of
// the backwards link
void **ListIndex(T_LIST *list, int index);

// Insert the data at the given index. Negative indexing
// works here as well. If the index is out of range, it just
// adds it to the side, where it left, but you can say
// "undefined behavior" if that makes you more comfortable.
// No special functions to adding to either side needed,
// Just insert to 0 and -1.
void ListInsert(T_LIST *list, void *data, int index);

// A helper function to make this task more obvious. Most useful
// when decomposing the list in a similar way to the dictionary.
// I could make a clear method that uses a callback, but we'll
// have enought of those elsewhere. (mainly serialization/
// deserialization)
int ListHasItems(T_LIST *list);

#endif // LIST_H