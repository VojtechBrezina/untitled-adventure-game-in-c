#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "dictionary.h"
#include "util.h"

#define SAVE_PATH ".saves"

// Loads the saves file and grabs all the save filenames
// from it. If the file doesn't exist, it creates one with
// no saves in it.
T_DICTIONARY *listSaves(){
    FILE *savesFile = fopen(SAVE_PATH, "r");

    if(!savesFile){
        FILE *created = fopen(SAVE_PATH, "w");
        fprintf(created, "0\n");
        fclose(created);
        return NULL;
    }

    T_DICTIONARY *result = NULL;
    int count = 0;
    char *line = simpleGetLine(savesFile);
    sscanf(line, "%d", &count);

    for(int i = 0; i < count; i++){
        char *line = simpleGetLine(savesFile);
        DictionaryInsert(&result, line, NULL);
        free(line);
        while(strcmp(line = simpleGetLine(savesFile), "#GAME_END"))
            free(line);
        free(line);
    }

    return result;
}

int main(void){
    printf("\nVitej v \"Untitled adventure game in c\" %s\n\n", GAME_VERSION);

    T_DICTIONARY *availableSaves = listSaves();

    T_LIST *savesList = DictionaryListKeys(&availableSaves);
    while(ListHasItems(savesList))
        printf("%s\n", (char *)ListRemove(savesList, 0));
    free(savesList);

    while(availableSaves)
        DictionaryRemoveSomething(&availableSaves);

    return EXIT_SUCCESS;
}