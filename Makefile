# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Isrc `sdl2-config --cflags`
LDFLAGS := -lm `sdl2-config --libs`

# Directories
SRCDIR := src
TARGET := bin/game

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJS)
