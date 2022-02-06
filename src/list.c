#include <stdlib.h>
#include <assert.h>

#include "list.h"

void ListInit(T_LIST *list){
    list->head = list->tail = NULL;
}

void **ListIndex(T_LIST *list, int index){
    // If we are in debug mode do a basic integrity check.
    assert(!!list->head == !!list->tail);

    // Pls no hate for the while(1), it seems to be the
    // cleanest way I can think of.
    if(index >= 0){
        int i = 0;
        T_LIST_NODE *node = list->head;
        while(1){
            if(!node)
                return NULL;
            if(i == index)
                return &node->data;
            i++;
            node = node->next;
        }
    }

    int i = -1;
    T_LIST_NODE *node = list->tail;
    while(1){
        if(!node)
            return NULL;
        if(i == index)
            return &node->data;
        i--;
        node = node->prev;
    }
}

// A helper function to make inserting cleaner.
// It can put the list in an invalid state, so it can
// and probably should stay hidden in this file.
void insertLeft(T_LIST_NODE *what, T_LIST_NODE *where){
    if(where){
        if(where->prev)
            where->prev->next = what;
        what->prev = where->prev;
        where->prev = what;
    }else{
        what->prev = NULL;
    }
    what->next = where;
}

// Same story as insertLeft. Now we can keep List insert
// under one screen tall and easy to read.
void insertRight(T_LIST_NODE *what, T_LIST_NODE *where){
    if(where){
        if(where->next)
            where->next->prev = what;
        what->next = where->next;
        where->next = what;
    }else{
        what->next = NULL;
    }
    what->prev = where;
}

void ListInsert(T_LIST *list, void *data, int index){
    T_LIST_NODE *node = malloc(sizeof(T_LIST_NODE));
    // Again using while(1) to make it easier. I am sorry.

    if(index >= 0){
        int i = 0;
        T_LIST_NODE *iter = list->head;
        while(1){
            if(i == index || !iter){
                insertLeft(node, iter);
                break;
            }
            iter = iter->next;
            i++;
        }
    }else{
        int i = -1;
        T_LIST_NODE *iter = list->tail;
        while(1){
            if(i == index || !iter){
                insertRight(node, iter);
                break;
            }
            iter = iter->prev;
            i--;
        }
    }

    // Make sure the ends are up to date
    if(!node->prev)
        list->head = node;

    if(!node->next)
        list->tail = node;

    // If we are in debug mode do a basic integrity check.
    assert(!!list->head == !!list->tail);
}

int ListHasItems(T_LIST *list){
    // If we are in debug mode do a basic integrity check.
    assert(!!list->head == !!list->tail);

    return !!list->head;
}

T_DYNAMIC_ARRAY *ListToDynamicArray(T_LIST *list){
    T_DYNAMIC_ARRAY *result = malloc(sizeof(T_DYNAMIC_ARRAY));
    DynamicArrayInit(result);

    for(T_LIST_NODE *iter = list->head; iter; iter = iter->next)
        DynamicArrayAppend(result, iter->data);

    return result;
}
