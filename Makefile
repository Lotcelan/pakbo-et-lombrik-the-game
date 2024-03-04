

CC := gcc
CFLAGS := -Wall -Wextra -Isrc `sdl2-config --cflags` -pedantic -MMD -MP
LDFLAGS := -lm `sdl2-config --libs` -I/usr/include -L/usr/lib/x86_64-linux-gnu -Isrc/engine/include -Isrc -Istructures -ljansson

# Directories
SRCDIR := src
BUILDDIR := build
TARGET := bin/game

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/engine/*.c) $(wildcard $(SRCDIR)/engine/structures/*.c) $(wildcard $(SRCDIR)/scenes/**/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default target
.PHONY: all
all: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilation
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build files
.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	rm -rf bin/*
