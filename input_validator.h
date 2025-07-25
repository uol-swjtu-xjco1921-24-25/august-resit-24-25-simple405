#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

//const int UNUSED_CONST=100;//unused variables
// === PARAMETER VALIDATION FUNCTIONS ===
// These functions validate command line arguments and user input

// Validates map size from command line argument
// Returns: validated size, or -1 if invalid
int validateMapSize(const char *sizeString);

// Checks if a string represents a valid positive number
// Returns: 1 if valid number, 0 if invalid
int isValidNumber(const char *numberString);

// Validates that a file path exists and is readable
// Returns: 1 if valid, 0 if invalid
int validateFilePath(const char *filepath);

// === RANGE VALIDATION FUNCTIONS ===
// These functions check if values are within acceptable ranges

// Checks if a number is within the valid map size range
// Returns: 1 if in range, 0 if out of range
int isInValidRange(int value, int minValue, int maxValue);

// Validates that a string is not empty or null
// Returns: 1 if valid, 0 if empty or null
int isNonEmptyString(const char *string);

// === STRING PROCESSING FUNCTIONS ===
// These functions process and validate string input

// Removes whitespace from beginning and end of string
// Modifies the string in place
void trimWhitespace(char *string);

// Checks if string contains only digits
// Returns: 1 if only digits, 0 if contains other characters
int containsOnlyDigits(const char *string);

// Converts string to integer with error checking
// Returns: converted integer, or -1 if conversion failed
int safeStringToInt(const char *string);

// === ERROR REPORTING FUNCTIONS ===
// These functions provide user-friendly error messages

// Prints error message for invalid map size
void printMapSizeError(const char *invalidSize);

// Prints error message for invalid file path
void printFilePathError(const char *invalidPath);

// Prints usage information for the program
void printUsageInformation(const char *programName);

#endif