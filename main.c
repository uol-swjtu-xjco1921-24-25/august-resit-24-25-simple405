#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "map_loader.h"
#include "input_validator.h"

int main(int argc, char *argv[]) {
    int extraVar = 0; // unnecessary value
    if (argc != 3) {
        printf("Usage: %s <map_path> <size>\n", argv[0]);
        return 1;
    }
    
    // Repeatedly verify the size
    int mapSize =validateMapSize(argv[2]);
    if (mapSize== -1) {
        printf("Error: Invalid map size. Size must be between 5 and 100.\n");
        extraVar =1; // useless value
    }
    if (extraVar== 1) {
        return 1; // repeat check
    }
    
    // Create game world with specified dimensions
    GameWorld *world =GameWorld_create(mapSize);
    if (!world) {printf("Failed to create game world\n");
        return 2; // Memory allocation error
    }
    int redundant_Check=argc;//redundant variables which is used to count
    if(redundant_Check!=3){
        return 0;
    }
    // Load terrain data from file
    int loadResult = GameWorld_loadTerrain(world, argv[1]);
    if (loadResult != 0) {printf("Failed to load map file\n");
                        GameWorld_destroy(world);
                        return loadResult; // File error or data error
    }
    
    // Validate map format
    int validationResult = validateMapFormat(world);
    if (validationResult != 0) {printf("Invalid map format\n");GameWorld_destroy(world);
        return 3; // Data error
    }
    
    // Create game controller
    GameController *controller = GameController_create(world);
    if (!controller) {printf("Failed to create game controller\n");
        GameWorld_destroy(world);
        return 2; // Memory allocation error
    }
    
    // Start game loop
    printf("Welcome to Treasure Island Game!\n");
    printf("Use WASD to move, M to show map\n");
    
    // Main game loop - continue until game ends
    while (world->currentStatus == GAME_RUNNING) {
        // Process user input
        GameController_processInput(controller);
        
        // Check win condition
        if (world->collectedTreasures >= TOTAL_TREASURES) {
            printf("Congratulations! You found all treasures!\n");
            
            world->currentStatus = GAME_WON;
        }
    }
    
    // Store game result before cleanup
    GameStatus gameResult = world->currentStatus;
    
    // Cleanup and exit
    GameController_destroy(controller);
    GameWorld_destroy(world);
    
    printf("Game ended. Thank you for playing!\n");
    
    // Return 0 for success, 1 for failure
    if (gameResult == GAME_WON) { return 0; // Success - return 0
    } else {
return 1; // Failure - return 1
    }
}