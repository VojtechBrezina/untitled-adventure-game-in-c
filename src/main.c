#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "dictionary.h"

// Holds the state of the main menu that
// lets you start a new game or load an
// existing one.
typedef struct{

} T_MAIN_MENU;

void MainMenuInit(){

}

int main(void){

    T_DICTIONARY *d = NULL;
    char *l = NULL;
    size_t n = 0, r;
    //FILE *f = fopen("test.txt", "r");
    FILE *f = fopen("/usr/share/dict/words", "r");
    while((r = getline(&l, &n, f)) != -1){
        l[r - 1] = '\0';
        DictionaryInsert(&d, l, NULL);
        l = NULL;
        n = 0;
    }
    fclose(f);
    free(l);
    n = 0;

    DictionaryOptimize(&d);

    while((r = getline(&l, &n, stdin)) != -1){
        n = 0;
        l[r - 1] = '\0';
        char *res = DictionarySearch(&d, l)->key;
        if(res) printf("> %s\n\n", res);
        else printf("> NULL\n\n");
        l = NULL;
    }

    T_GAME *game;

    printf("\nVitej v \"Untitled adventure game in c\" %s\n\n", GAME_VERSION);

    return EXIT_SUCCESS;
}