# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Isrc `sdl2-config --cflags`
LDFLAGS := -lm `sdl2-config --libs`

# Directories
SRCDIR := src
BUILDDIR := build
TARGET := bin/game

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/engine/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default target
.PHONY: all
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
    $(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilation
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
    $(CC) $(CFLAGS) -MMD -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build files
.PHONY: clean
clean:
    rm -rf $(BUILDDIR) $(TARGET)

# Print help message
.PHONY: help
help:
    @echo "Usage: make [target]"
    @echo ""
    @echo "Targets:"
    @echo "  all        : Build the game (default)"
    @echo "  clean      : Clean build files"
    @echo "  help       : Print this help message"
