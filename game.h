#ifndef GAME_H
#define GAME_H

// Map size limits - these define the minimum and maximum allowed map dimensions
#define MAX_MAP_SIZE 100
#define MIN_MAP_SIZE 5
#define TOTAL_TREASURES 3

// Cell types enumeration - defines what each character on the map represents
typedef enum {
    CELL_WATER = 'w',      // Water cells - player cannot move here
    CELL_LAND = ' ',       // Empty land - player can move here
    CELL_TREE = 'T',       // Tree obstacle - blocks player movement
    CELL_TREASURE = 'H',   // Hidden treasure - player can collect these
    CELL_START = 'S',      // Starting position - where player begins
    CELL_PLAYER = 'X'      // Player symbol - shows current player position
} CellType;

// Game status enumeration - tracks the current state of the game
typedef enum {
    GAME_RUNNING,          // Game is currently active
    GAME_WON,            // Player has won the game
    // delete GAME_QUIT status
    GAME_EXTRA=99
} GameStatus;

// 2D position structure - represents a location on the map
typedef struct {
    int row;              // Vertical position (y-coordinate)
    int col;              // Horizontal position (x-coordinate)
} Vector2D;

// Game world structure - contains all map and game state information
typedef struct {
    CellType **terrain;           // 2D array storing the map layout
    CellType **visibility;        // 2D array tracking what player can see
    int dimensions;               // Size of the square map (width and height)
    Vector2D playerLocation;      // Current position of the player
    Vector2D spawnPoint;         // Starting position where player began
    int collectedTreasures;      // Number of treasures found so far
    GameStatus currentStatus;     // Current state of the game
} GameWorld;

// Game controller structure - manages user input and game flow
typedef struct {
    GameWorld *world;            // Pointer to the game world
    char lastCommand;            // Last command entered by player
    int moveCount;               // Total number of moves made
} GameController;

// Event structure - represents game events like movement or treasure finding
typedef struct {
    int eventType;               // Type of event that occurred
    Vector2D position;           // Position where event happened
    char data;                   // Additional data about the event
} GameEvent;

// Stream reader structure - for reading map files efficiently
typedef struct {
    void *stream;                // File stream pointer
    char *buffer;                // Buffer for reading data
    int bufferSize;              // Size of the buffer
    int currentPos;              // Current position in buffer
} StreamReader;

// === GAME WORLD FUNCTIONS ===
// These functions manage the game world and its state

// Creates a new game world with specified size
// Returns: pointer to new GameWorld, or NULL if creation failed
GameWorld* GameWorld_create(int size);

// Destroys a game world and frees all memory
// Parameters: world - pointer to GameWorld to destroy
void GameWorld_destroy(GameWorld *world);

// Loads map terrain from a file into the game world
// Returns: 0 for success, error code for failure
int GameWorld_loadTerrain(GameWorld *world, const char *filepath);

// Updates the game world based on player input
// Returns: new game status after update
GameStatus GameWorld_update(GameWorld *world, char input);

// Renders the current game world to the screen
void GameWorld_render(GameWorld *world);

// Updates what the player can see around their position
void GameWorld_updateVisibility(GameWorld *world, Vector2D position);

// === GAME CONTROLLER FUNCTIONS ===
// These functions handle user input and game control

// Creates a new game controller for the specified world
GameController* GameController_create(GameWorld *world);

// Destroys a game controller and frees memory
void GameController_destroy(GameController *controller);

// Processes user input and updates the game accordingly
void GameController_processInput(GameController *controller);

// === UTILITY FUNCTIONS ===
// Helper functions for game logic

// Checks if a cell type is valid for the game
// Returns: 1 if valid, 0 if invalid
int isValidCellType(CellType cellType);

// Processes player movement to a new position
void processMovement(GameWorld *world, Vector2D newPos);

// Handles game events like treasure collection
void handleEvent(GameWorld *world, GameEvent event);

// Validates terrain boundaries (water border check)
int validateTerrainBoundaries(GameWorld *world);

#endif