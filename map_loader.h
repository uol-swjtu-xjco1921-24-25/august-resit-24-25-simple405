#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "game.h"

//redundant function announcement
// === STREAM READER FUNCTIONS ===
// These functions handle efficient file reading

// Creates a new stream reader for reading map files
// Returns: pointer to StreamReader, or NULL if creation failed
StreamReader* createStreamReader(const char *filename);

// Destroys a stream reader and closes the file
void destroyStreamReader(StreamReader *reader);

// Reads the next character from the stream
// Returns: character read, or EOF if end of file
int StreamReader_getNextChar(StreamReader *reader);

// === MAP LOADING FUNCTIONS ===
// These functions load and validate map data

// Loads terrain data from file into game world
// Returns: 0 for success, 2 for file error, 3 for data error
int loadTerrainFromFile(GameWorld *world, const char *filepath);

// Validates that the loaded map has correct format
// Returns: 0 for success, 3 for validation error
int validateMapFormat(GameWorld *world);

// Checks that map boundaries are all water cells
// Returns: 0 for success, 3 for boundary error
int validateMapBoundaries(GameWorld *world);

// Counts how many times a specific cell type appears in map
// Returns: number of occurrences found
int countCellType(GameWorld *world, CellType cellType);

// Validates that all characters in map are allowed
// Returns: 0 for success, 3 for invalid character error
int validateMapCharacters(GameWorld *world);

// === HELPER FUNCTIONS ===
// Utility functions for map processing

// Checks if a character represents a valid cell type
// Returns: 1 if valid, 0 if invalid
int isValidMapCharacter(char character);

// Converts a character to its corresponding CellType
// Returns: CellType enum value
CellType charToCellType(char character);

// Gets the dimensions of a map file before loading
// Returns: size of map, or 0 if invalid
int getMapDimensions(const char *filepath);

#endif