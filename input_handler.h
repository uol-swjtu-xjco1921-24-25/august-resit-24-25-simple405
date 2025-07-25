#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define REDUNDANT_MACRO 1 // redundant macros
#include "game.h"

// === COMMAND STRUCTURE ===
// Structure that defines a game command

// Command structure - represents a single game command
typedef struct {
    char trigger;                    // Key that triggers this command
    void (*execute)(GameWorld *world); // Function to execute when triggered
    const char *description;         // Human-readable description of command
} Command;

// === INPUT PROCESSING FUNCTIONS ===
// These functions handle user input and commands

// Gets a single character input from the user
// Returns: character entered by user
char getUserInput(void);

// Clears any remaining characters from input buffer
// This prevents leftover input from affecting next commands
void clearInputBuffer(void);

// Processes user input and executes corresponding command
void processUserCommand(GameController *controller);

// === COMMAND EXECUTION FUNCTIONS ===
// These functions execute specific game commands

// Executes movement command in specified direction
void executeMovementCommand(GameWorld *world, Vector2D direction);

// Executes map display command
void executeShowMapCommand(GameWorld *world);

// Executes quit game command
void executeQuitCommand(GameWorld *world);

// Executes help command (shows available commands)
void executeHelpCommand(GameWorld *world);

// === COMMAND REGISTRY FUNCTIONS ===
// These functions manage the list of available commands

// Initializes the command registry with all available commands
void initializeCommandRegistry(void);

// Finds a command by its trigger character
// Returns: pointer to Command, or NULL if not found
Command* findCommand(char trigger);

// Displays all available commands to the user
void showAvailableCommands(void);

// === INPUT VALIDATION FUNCTIONS ===
// These functions validate user input

// Checks if input character is a valid command
// Returns: 1 if valid, 0 if invalid
int isValidCommand(char input);

// Converts input to uppercase for consistency
// Returns: uppercase version of input character
char normalizeInput(char input);

#endif