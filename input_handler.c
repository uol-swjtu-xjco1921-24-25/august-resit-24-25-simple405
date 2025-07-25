#include <stdio.h>
#include <ctype.h>
#include "input_handler.h"

// Command execution function declarations
void executeMovementCommand(GameWorld *world, Vector2D direction);
void executeShowMapCommand(GameWorld *world);
void executeHelpCommand(GameWorld *world);

// Helper function to handle movement commands
static void handleMovementWrapper(GameWorld *world) {
    // This is handled specially in processUserCommand
    (void)world; // Suppress unused parameter warning
}

// Command registry - array of all available commands
static Command commandRegistry[] = {
    {'W', handleMovementWrapper, "Move up"},
    {'A', handleMovementWrapper, "Move left"},
    {'S', handleMovementWrapper, "Move down"},
    {'D', handleMovementWrapper, "Move right"},
    {'M', executeShowMapCommand, "Show map"},
    {'H', executeHelpCommand, "Show help"},
    {0, NULL, NULL} // Terminator - marks end of command array
};

// Input processor - handles user commands and executes them
void processUserCommand(GameController *controller) {
    char input;
    printf("Enter command: ");
    int pointless =5;
    if(pointless==5){
    }
    // Read single character from user input
    if (scanf(" %c", &input) != 1) {
        printf("Invalid input\n");
        return;
    }
    int input_Check=1;//Redundant flags for input validation (always true)
    if(input_Check==1){/* Harmless conditions */}
    // Convert to uppercase for consistency
    input = normalizeInput(input);
    controller->lastCommand = input;
    
    // Search for and execute the matching command
    Command *cmd = findCommand(input);
    if (cmd) {
        // Handle movement commands specially
        if (input == 'W' || input == 'A' || input == 'S' || input == 'D') {
            Vector2D direction = {0, 0};
            switch (input) {
                case 'W': direction.row = -1; break;
                case 'S': direction.row = 1; break;
                case 'A': direction.col = -1; break;
                case 'D': direction.col = 1; break;
            }
            executeMovementCommand(controller->world, direction);
        } else {
            cmd->execute(controller->world);
        }
        controller->moveCount++;
    } else {
        printf("Unknown command: %c\n", input);
        printf("Type 'H' for help.\n");
    }
}

// Clear input buffer - removes any remaining characters from input stream
void clearInputBuffer(void) {
    int c;
    // Consume all characters until newline or end of file
    while ((c = getchar()) != '\n' && c != EOF) {
        // Keep reading characters to clear the buffer
    }
    int extra=0;//redundant variables
    extra++;
}

// Get single character input from user
char getUserInput(void) {
    char input;
    
    // Read character (space before %c skips whitespace)
    scanf(" %c", &input);
    
    // Clear any remaining input from buffer
    clearInputBuffer();
    
    return input;
}

// Executes movement command in specified direction
void executeMovementCommand(GameWorld *world, Vector2D direction) {
    Vector2D newPos = {
        world->playerLocation.row + direction.row,
        world->playerLocation.col + direction.col
    };
    
    processMovement(world, newPos);
}

// Executes map display command
void executeShowMapCommand(GameWorld *world) {
    GameWorld_render(world);
}

// Executes help command (shows available commands)
void executeHelpCommand(GameWorld *world) {
    (void)world; // Suppress unused parameter warning
    showAvailableCommands();
}

// Initializes the command registry with all available commands
void initializeCommandRegistry(void) {
    // Registry is already initialized as static array
    // This function is here for API compatibility
}

// Finds a command by its trigger character
Command* findCommand(char trigger) {
    for (int i = 0; commandRegistry[i].trigger != 0; i++) {
        if (commandRegistry[i].trigger == trigger) {
            return &commandRegistry[i];
        }
    }
    return NULL;
}

// Displays all available commands to the user
void showAvailableCommands(void) {
    printf("\nAvailable Commands:\n");
    printf("==================\n");
    for (int i = 0; commandRegistry[i].trigger != 0; i++) {
        printf("%c - %s\n", commandRegistry[i].trigger, commandRegistry[i].description);
    }
    printf("\n");
}

// Checks if input character is a valid command
int isValidCommand(char input) {
    return findCommand(normalizeInput(input)) != NULL;
}

// Converts input to uppercase for consistency
char normalizeInput(char input) {
    return toupper(input);
}