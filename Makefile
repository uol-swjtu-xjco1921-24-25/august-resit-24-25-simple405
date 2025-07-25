# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target executable
TARGET = island

# Source files
SOURCES = main.c game.c map_loader.c input_validator.c input_handler.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean