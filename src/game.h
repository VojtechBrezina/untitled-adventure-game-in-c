#ifndef GAME_H
#define GAME_H

// The version of the game that is used to
// determine save compatibility.
#define GAME_VERSION "v0.0.0"

// This struct holds the entire game state.
typedef struct{

} T_GAME;

// Initialize the game at the very start.
void GameInit(T_GAME *game);

// Initialize the game from a sved state.
void GameLoad(T_GAME *game, const char *name);

// Save the game state.
void GameSave(T_GAME *game, const char *name);

// Clean all memory owned by the game when
// no longer needed.
void GameDone(T_GAME * game);

// Process one command from the user and
// dispose of it. Returns a logical value
// stating whether the game should continue
// or not for the main loop.
int GameProcessCommand(char *command);

#endif // GAME_H
