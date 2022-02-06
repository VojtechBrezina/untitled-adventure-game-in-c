#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    // Follows a little utility for playing with the
    // dictionary using the "/usr/share/dict/words"
    // file. Thi is messy and serves no purpose in
    // the actual project, but will be archived under
    // the v0.0.1 tag.

    printf(
        "Vitej v testovacim programu. ("GAME_VERSION")\n"
        "V pameti je slovnik inicializovany slovy z\n"
        "/usr/share/dict/words Tento program slouzi\n"
        "k interaktivnimu volani knihovnich funkci\n"
        "nasledujicim zpusobem:\n"
        "prikaz slovo\n"
        "kde prikz je: s = search, g = get, i = insert, r = remove\n"
        "Ctrl+D pro ukonceni.\n\n"
    );

    T_DICTIONARY *d = NULL;
    char *l = NULL;
    size_t n = 0, r;
    int count = 0;
    FILE *f = fopen("/usr/share/dict/words", "r");
    while((r = getline(&l, &n, f)) != -1){
        l[r - 1] = '\0';
        DictionaryInsert(&d, l, NULL);
        l = NULL;
        n = 0;
        count++;
        if(count % 1000 == 0)
            DictionaryOptimize(&d);
    }
    fclose(f);
    free(l);
    n = 0;

    DictionaryOptimize(&d);

    while((r = getline(&l, &n, stdin)) != -1){
        n = 0;
        l[r - 1] = '\0';
        char cmd = l[0];
        char *w = l + 1;
        while(*w && isspace(*w))
            w++;
        switch (cmd){
            case 's': case 'S':{
                const char *res = DictionarySearch(&d, w)->key;
                if(res) printf("> %s\n\n", res);
                else printf("> NULL\n\n");
                break;
            }
            case 'i': case 'I':
                DictionaryInsert(&d, w, NULL);
                printf("> OK\n\n");
                break;
            case 'g': case 'G':
                printf("> %s\n\n", DictionaryGet(&d, w) ? "YES" : "NO");
                break;
            case 'r': case 'R':
                DictionaryRemove(&d, w);
                printf("> OK\n\n");
                break;
            default:
                printf("> ?\n\n");
                break;
        }

        l = NULL;
    }



    T_GAME *game;

    // printf("\nVitej v \"Untitled adventure game in c\" %s\n\n", GAME_VERSION);

    return EXIT_SUCCESS;
}