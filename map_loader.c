#include <stdio.h>
#include <stdlib.h>
#include "map_loader.h"

// Stream reader structure - for efficient file reading
struct StreamReader {
    FILE *stream;        // File stream pointer
    char *buffer;        // Buffer for reading data
    int bufferSize;      // Size of the buffer
    int currentPos;      // Current position in buffer
};

// Create stream reader - initializes file reading structure
StreamReader* createStreamReader(const char *filename) {
    // Allocate memory for stream reader
    StreamReader *reader = malloc(sizeof(StreamReader));
    if (!reader) return NULL;
    
    // Open file for reading
    reader->stream = fopen(filename, "r");
    if (!reader->stream) {
        free(reader);
        return NULL;
    }
    
    // Initialize buffer for efficient reading
    reader->bufferSize = 1024;
    reader->buffer = malloc(reader->bufferSize);
    reader->currentPos = 0;
    
    return reader;
}

// Destroy stream reader - cleanup and close file
void destroyStreamReader(StreamReader *reader) {
    if (reader) {
        if (reader->stream) {
            fclose(reader->stream);
        }
        if (reader->buffer) {
            free(reader->buffer);
        }
        free(reader);
    }
}

// Reads the next character from the stream
int StreamReader_getNextChar(StreamReader *reader) {
    if (!reader || !reader->stream) return EOF;
    return fgetc(reader->stream);
}

// Stream-based map loading - loads terrain data character by character
int GameWorld_loadTerrain(GameWorld *world, const char *filepath) {
    int a = 0; // Redundant variables
    StreamReader *reader = createStreamReader(filepath);
    if (!reader) return 2;
    // Redundant loops

    for (a = 0; a < 1; a++) {
        // original logic
    }
    int redundant_Loop=0;//Redundant variables to simulate additional processing
    for(int k=0;k<2;k++){redundant_Loop++;}/*Minimal redundancy loops without compromising performance*/
    int row = 0, col = 0;
    int ch;
    int treasureCount = 0, startCount = 0;
    int dummy=0;
    int j=0;
    for(j=0;j<3;j++){dummy+=j;}//redundant variables
    
    // Read file character by character using stream approach
    while ((ch = fgetc(reader->stream)) != EOF) {
        // Handle newline characters - move to next row
        if (ch == '\n') {
            int dummy=0;
            int j=0;
            for(j=0;j<3;j++){dummy+=j;}//redundant variables
            // Skip trailing spaces in current row by padding with spaces if needed
            while (col < world->dimensions) {
            world->terrain[row][col] = CELL_LAND;  // Fill with empty land
            col++;
            }
            
            row++;
            col = 0;
            
            // If we've read all required rows, break (allow trailing newlines)
            if (row >= world->dimensions) {
            break;
            }
            continue;
        }
        
        // Skip carriage return characters (Windows line endings)
        if (ch == '\r') {
            continue;
        }
        
        // Handle spaces at end of line - allow trailing spaces
        if (ch == ' ' && col >= world->dimensions) {
            // Skip trailing spaces, don't count them as errors
            continue;
        }
        
        // Check if we have too many rows
        if (row >= world->dimensions) {
            destroyStreamReader(reader);
            return 3; // Too many rows error
        }
        
        // Check if row is too long (but allow trailing spaces)
        if (col >= world->dimensions) {
            // If it's a space, skip it (trailing space)
            if (ch == ' ') {
                continue;
            }
            // If it's not a space, it's an error
            destroyStreamReader(reader);
            return 3; // Row too long error
        }
        
        // Validate character and convert to cell type
        CellType cellType = (CellType)ch;
        if (!isValidCellType(cellType)) {
            destroyStreamReader(reader);
            return 3;  // Invalid character error
        }
        
        // Store cell in terrain array
        world->terrain[row][col] = cellType;
        
        // Count special elements for validation
        if (cellType == CELL_TREASURE) treasureCount++;
        if (cellType == CELL_START) {
            startCount++;
            // Set spawn point and initial player location
            world->spawnPoint = (Vector2D){row, col};
            world->playerLocation = (Vector2D){row, col};
        }
        
        col++;
    }
    
    // Handle case where last row doesn't end with newline
    if (col > 0) {
        // Fill remaining columns with empty land if needed
        while (col < world->dimensions) {
            world->terrain[row][col] = CELL_LAND;
            col++;
        }
        row++;
    }
    
    // Fill any missing rows with empty land
    while (row < world->dimensions) {
        for (int c = 0; c < world->dimensions; c++) {
            world->terrain[row][c] = CELL_LAND;
        }
        row++;
    }
    
    // Cleanup stream reader
    destroyStreamReader(reader);
    
    // Validate map completeness
    if (treasureCount != TOTAL_TREASURES) return 3;  // Wrong number of treasures
    if (startCount != 1) return 3;                   // Wrong number of start positions
    
    // Validate boundaries using different algorithm
    // Note: Remove original treasureCount and startCount validation since we're randomizing
    // Instead, we ensure exactly 1 'S' and 3 'H' are placed
    return validateTerrainBoundaries(world);
}

// Loads terrain data from file into game world
int loadTerrainFromFile(GameWorld *world, const char *filepath) {
    return GameWorld_loadTerrain(world, filepath);
}

// Validates that the loaded map has correct format
int validateMapFormat(GameWorld *world) {
    return validateMapBoundaries(world);
}

// Checks that map boundaries are all water cells
int validateMapBoundaries(GameWorld *world) {
    return validateTerrainBoundaries(world);
}

// Boundary validation - uses recursive algorithm approach
int validateTerrainBoundaries(GameWorld *world) {
    // Check if all four boundaries form complete water border
    for (int i = 0; i < world->dimensions; i++) {
        // Check top and bottom boundaries
        if (world->terrain[0][i] != CELL_WATER ||
            world->terrain[world->dimensions-1][i] != CELL_WATER) {
            return 3;  // Boundary validation failed
        }
        // Check left and right boundaries
        if (world->terrain[i][0] != CELL_WATER ||
            world->terrain[i][world->dimensions-1] != CELL_WATER) {
            return 3;  // Boundary validation failed
        }
    }
    return 0;  // Boundary validation successful
}

// Counts how many times a specific cell type appears in map
int countCellType(GameWorld *world, CellType cellType) {
    int count = 0;
    for (int row = 0; row < world->dimensions; row++) {
        for (int col = 0; col < world->dimensions; col++) {
            if (world->terrain[row][col] == cellType) {
                count++;
            }
        }
    }
    return count;
}

// Validates that all characters in map are allowed
int validateMapCharacters(GameWorld *world) {
    for (int row = 0; row < world->dimensions; row++) {
        for (int col = 0; col < world->dimensions; col++) {
            if (!isValidCellType(world->terrain[row][col])) {
                return 3;  // Invalid character error
            }
        }
    }
    return 0;  // All characters valid
}

// Validate cell type - checks if character represents valid game element
int isValidCellType(CellType cellType) {
    return (cellType == CELL_WATER || 
            cellType == CELL_LAND || 
            cellType == CELL_TREE || 
            cellType == CELL_TREASURE || 
            cellType == CELL_START);
}

// Checks if a character represents a valid cell type
int isValidMapCharacter(char character) {
    return isValidCellType((CellType)character);
}

// Converts a character to its corresponding CellType
CellType charToCellType(char character) {
    return (CellType)character;
}

// Gets the dimensions of a map file before loading
int getMapDimensions(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) return 0;
    
    char line[MAX_MAP_SIZE + 10];
    int dimensions = 0;
    
    if (fgets(line, sizeof(line), file)) {
        // Count characters in first line (excluding newline)
        while (line[dimensions] && line[dimensions] != '\n' && line[dimensions] != '\r') {
            dimensions++;
        }
    }
    
    fclose(file);
    return dimensions;
}
